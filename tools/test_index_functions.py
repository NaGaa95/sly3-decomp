"""Verify explicit non-function exclusions against discovered and maintained code."""
import contextlib
import csv
import importlib.util
import io
from pathlib import Path
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[1]


def check_index_exclusions(module_path=None):
    module_path = Path(module_path) if module_path else ROOT / "tools/index_functions.py"
    sys.path.insert(0, str(ROOT / "tools"))
    spec = importlib.util.spec_from_file_location("index_exclusion_test_subject", module_path)
    subject = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(subject)
    tested = 0
    test_root = ROOT / "build/tests/index_exclusions"
    test_root.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="sly3-index-", dir=test_root) as temporary:
        workspace = Path(temporary).resolve()
        assert workspace.parent == test_root.resolve()
        (workspace / "config").mkdir()
        (workspace / "build/reports").mkdir(parents=True)
        subject.ROOT = workspace
        subject.target_config = lambda: {
            "text": {"addr": 0x1000, "size": 0x100}, "entry": 0x1000
        }
        (workspace / "build/reports/spim_functions.csv").write_text(
            "address,file,name\n1000,SCUS_974,entry\n1020,SCUS_974,orphan\n1040,SCUS_974,next\n"
        )
        (workspace / "build/reports/ghidra_functions.csv").write_text("Start\n0x1020\n")
        override_header = "Name,Start,End,Size,BoundarySource\n"
        default_overrides = (
            override_header + "entry,0x1000,0x1020,32,verified\n"
            "actual,0x1030,0x1040,16,reviewed\n"
        )
        (workspace / "config/matched.csv").write_text(
            "address,instructions\n0x1000,8\n"
        )
        excluded = workspace / "config/function_exclusions.csv"
        overrides = workspace / "config/function_overrides.csv"
        output = workspace / "config/functions.csv"

        def run(exclusions=None, override_text=default_overrides):
            overrides.write_text(override_text)
            if exclusions is None:
                excluded.unlink(missing_ok=True)
            else:
                excluded.write_text(exclusions)
            with contextlib.redirect_stdout(io.StringIO()):
                subject.main()
            with output.open(newline="") as stream:
                return {int(row["Start"], 16): row for row in csv.DictReader(stream)}

        initial = run()
        assert set(initial) == {0x1000, 0x1020, 0x1030, 0x1040}
        tested += 1
        valid = "Start,End,Reason\n0x1020,0x1030,reviewed-orphan\n"
        corrected = run(valid)
        assert set(corrected) == {0x1000, 0x1030, 0x1040}
        assert all(initial[address] == corrected[address] for address in corrected)
        tested += 1
        header = "Start,End,Reason\n"
        invalid = [
            "Start,End\n0x1020,0x1030\n",
            header + "0x1020,0x1030\n",
            header + "0x1020,0x1030,reason,extra\n",
            header + "0x1020,0x1030, \n",
            header + "0x0FFC,0x1030,reason\n",
            header + "0x1020,0x1104,reason\n",
            header + "0x1021,0x1030,reason\n",
            header + "0x1020,0x1031,reason\n",
            header + "0x1020,0x1020,reason\n",
            header + "0x1030,0x1020,reason\n",
            header + "0x1020,0x1030,a\n0x1020,0x1030,b\n",
            header + "0x1020,0x1030,a\n0x1028,0x1034,b\n",
            header + "0x1000,0x1004,entry\n",
            header + "0x1004,0x1008,maintained-body\n",
            header + "0x1030,0x1034,override-start\n",
            header + "0x1034,0x1038,override-interior\n",
        ]
        for value in invalid:
            prior = output.read_bytes()
            try:
                run(value)
            except ValueError:
                assert output.read_bytes() == prior
            else:
                raise AssertionError("Unsafe exclusion accepted: " + repr(value))
            tested += 1
        adjacent = run(header + "0x1020,0x1028,a\n0x1028,0x1030,b\n")
        assert adjacent == corrected
        tested += 1
    print(f"Index exclusion checks passed: {tested}")


if __name__ == "__main__":
    check_index_exclusions(sys.argv[1] if len(sys.argv) > 1 else None)

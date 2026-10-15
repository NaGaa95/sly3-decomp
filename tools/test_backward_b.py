"""Native positive match and conservative negative branch-policy checks."""
from pathlib import Path
import os
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))


def main():
    from asfix_backward_b import fix
    from compiler import compile_source
    from matchtool import compare_object

    source = ROOT / "src/hand/func_00255418.c"
    output = ROOT / "build/tests/backward_b/func_00255418.o"
    old_force = os.environ.get("SLY3_FORCE_COMPILE")
    os.environ["SLY3_FORCE_COMPILE"] = "1"
    try:
        compile_source(source, output)
    finally:
        if old_force is None:
            os.environ.pop("SLY3_FORCE_COMPILE", None)
        else:
            os.environ["SLY3_FORCE_COMPILE"] = old_force
    comparison = compare_object("func_00255418", output)
    assert comparison["status"] == "EXACT_MATCH", comparison
    raw = output.with_suffix(".raw.s").read_text()
    anchor = "\tb\t$L19\n\tmove\t$2,$0"
    assert anchor in raw

    def count(text):
        return len(fix(text)[1]["pinned_branches"])

    assert count(raw) == 1
    assert count(raw.replace(anchor, "\tb\texternal_label\n\tmove\t$2,$0")) == 0
    assert count(raw.replace(anchor, "\tb\t$L23\n\tmove\t$2,$0")) == 0
    assert count(raw.replace(anchor, "\tb\t$L19\n\tli\t$2,0x12345678")) == 0
    assert count(raw.replace(anchor, "\tb\t$L19\n$delay_label:\n\tmove\t$2,$0")) == 0
    assert count(raw.replace(anchor, "\tb\t$L19\n\tmove\t$2,$0\n\t.set noreorder")) == 0
    assert count(raw.replace("$L24:\n", "$L24:\n\t.org 0\n")) == 0
    assert count(raw.replace("$L24:\n", "$L24:\n" + "\tnop\n" * 2000)) == 0
    for opaque in ("#APP\n", "\t.word 0x1000FFFB\n", "\t.space 16\n"):
        try:
            fix(raw.replace("$L24:\n", "$L24:\n" + opaque))
        except ValueError:
            pass
        else:
            raise AssertionError("Opaque input was accepted: " + opaque)
    print("Fresh native EXACT_MATCH and 11 branch-policy guard checks passed")


if __name__ == "__main__":
    main()

"""Validate native toolchain behavior against real Sly 2 and Sly 3 code."""
import csv
import re
import subprocess
from common import ROOT, Elf32, save_json
from compiler import compile_source
from matchtool import compare, object_functions, functions


def main():
    reference = ROOT / "references/sly2"
    known = {}
    for row in csv.DictReader((reference / "config/functions.csv").open()):
        known[row["Name"]] = (int(row["Start"], 16), int(row["End"], 16) - int(row["Start"], 16))
    by_addr = {a: s for a, s in known.values()}
    for line in (reference / "config/symbol_addrs.txt").read_text().splitlines():
        match = re.match(r"(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if match and int(match[2], 16) in by_addr:
            address = int(match[2], 16)
            known[match[1]] = (address, by_addr[address])
    output = compile_source(reference / "src/P2/bis.cpp", ROOT / "build/smoke/sly2_bis.o", [reference / "include"])
    compiled = object_functions(output)
    original = Elf32((reference / "disc/SCUS_973.16").read_bytes())
    results = []
    for name, (code, rel) in compiled.items():
        if name.startswith("__tf"):
            continue  # Compiler-generated RTTI helper, absent from Sly 2's function map.
        result = compare(name, code, rel, original, known)
        if result["status"] not in ("EXACT_MATCH", "NORMALIZED_MATCH"):
            raise AssertionError(f"Sly 2 compiler regression: {name}: {result['status']}")
        results.append({k: v for k, v in result.items() if k not in ("target", "compiled", "differences")})
    assert len(results) >= 20, "Too few reference functions were validated"
    # A few independently identified unchanged leaf methods also exercise Sly 3's reader.
    leafs = {"Close__18CBinaryInputStream": "func_00118C30", "Align__18CBinaryInputStreami": "func_00118DC0", "SetDecompress__18CBinaryInputStreamiPUc": "func_00118E10"}
    sly3_results = []
    for source, target in leafs.items():
        code, rel = compiled[source]
        result = compare(target, code, rel)
        if result["status"] != "EXACT_MATCH":
            raise AssertionError(f"Sly 3 leaf validation failed: {target}: {result['status']}")
        changed = list(code)
        changed[0] ^= 1
        assert compare(target, changed, rel)["status"] == "DIFFERENT", "Matcher accepted a changed instruction"
        sly3_results.append({k: v for k, v in result.items() if k not in ("target", "compiled", "differences")})
    save_json(ROOT / "build/reports/compiler_validation.json", {"sly2": results, "sly3_leafs": sly3_results, "negative_comparison_checks": len(sly3_results), "note": "Leaf validation does not establish Sly 3's compiler identity for all engine or SDK code."})
    print(f"PASS: {len(results)} Sly 2 reference functions, {len(sly3_results)} exact Sly 3 leaf functions, and changed-instruction rejection")
    from test_relocations import main as test_relocations
    from test_sdk_filter import main as test_sdk_filter
    from test_fdlibm_filter import main as test_fdlibm_filter
    from test_memory_filter import main as test_memory_filter
    from test_data import main as test_data
    from test_sdk_gp64 import main as test_sdk_gp64
    from test_sdk_softdf import main as test_sdk_softdf
    from test_sdk_literals import main as test_sdk_literals
    from test_backward_b import main as test_backward_b
    from test_object_bindings import main as test_object_bindings
    from test_branch_fold import main as test_branch_fold
    from test_switch_tables import main as test_switch_tables
    from test_engine_exit_slots import main as test_engine_exit_slots
    test_relocations()
    test_sdk_filter()
    test_fdlibm_filter()
    test_memory_filter()
    test_data()
    test_sdk_gp64()
    test_sdk_softdf()
    test_sdk_literals()
    test_backward_b()
    test_object_bindings()
    test_branch_fold()
    test_switch_tables()
    test_engine_exit_slots()


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as error:
        print(error.stdout or "", error.stderr or "")
        raise SystemExit(error.returncode)

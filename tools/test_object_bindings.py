"""Verify scoped C++ startup placement and refuse ambiguous selectors."""
from copy import deepcopy
from common import ROOT, save_json
from compiler import compile_source
from matchtool import functions, compare_object
from object_bindings import source_bindings
from relocate import ObjectLinker, symbol_addresses


def main():
    source = ROOT / "src/P2/heap_init.cpp"
    output = compile_source(source, ROOT / "build/tests/heap_init.o")
    known, addresses = functions(), symbol_addresses()
    configuration = {"src/P2/heap_init.cpp": {
        "__static_initialization_and_destruction_0": "0x00117F48",
        "_GLOBAL_$I$*": "0x001180B8"}}
    scoped, bindings = source_bindings(source, output, known, addresses, configuration)
    local = [name for name in scoped if name not in known]
    assert len(local) == 2, local
    linker = ObjectLinker(output, addresses=bindings)
    results = [compare_object(name, output, known=scoped, linker=linker) for name in local]
    assert all(row["status"] == "LINKED_MATCH" for row in results), results
    assert "__static_initialization_and_destruction_0" not in known
    unrelated, unrelated_addresses = source_bindings(ROOT / "src/P2/bis.cpp", output, known, addresses, configuration)
    assert unrelated == known and unrelated_addresses == addresses
    rejected = []
    cases = {
        "missing selector": {"missing_helper": "0x00117F48"},
        "ambiguous prefix": {"_*": "0x00117F48"},
        "unindexed target": {"__static_initialization_and_destruction_0": "0x00117F4C"},
        "unsupported wildcard": {"*helper*": "0x00117F48"},
        "duplicate selector": {"__static_initialization_and_destruction_0": "0x00117F48",
                               "__static_*": "0x00117F48"},
    }
    for label, entries in cases.items():
        try:
            source_bindings(source, output, known, addresses, {"src/P2/heap_init.cpp": entries})
        except ValueError:
            rejected.append(label)
        else:
            raise AssertionError("Invalid scoped binding accepted: " + label)
    wrong = deepcopy(configuration)
    wrong["src/P2/heap_init.cpp"]["__static_initialization_and_destruction_0"] = "0x001180B8"
    bad_known, bad_addresses = source_bindings(source, output, known, addresses, wrong)
    result = compare_object("__static_initialization_and_destruction_0", output,
                            known=bad_known, linker=ObjectLinker(output, addresses=bad_addresses))
    assert result["status"] == "DIFFERENT", result
    save_json(ROOT / "build/reports/object_bindings_validation.json", {
        "functions": [{k: v for k, v in row.items() if k not in ("target", "compiled", "differences")}
                      for row in results],
        "unrelated_source_unmodified": True, "rejected_cases": rejected,
        "wrong_indexed_placement_rejected_by_byte_comparison": True})
    print("PASS: two scoped C++ initializers; five invalid bindings and wrong placement refused")


if __name__ == "__main__":
    main()

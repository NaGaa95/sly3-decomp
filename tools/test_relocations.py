"""Exercise strict matching with real compiled objects and corrupted operands."""
import struct
from common import ROOT, Elf32, save_json
from matchtool import compare, compare_object, object_functions
from relocate import ObjectLinker, symbol_addresses
from compiler import compile_source


def main():
    path = ROOT / "build/obj/hand/func_001054C0.o"
    name = "func_001054C0"
    compile_source(ROOT / "src/hand/func_001054C0.cpp", path)
    addresses = symbol_addresses()
    accepted = compare_object(name, path)
    assert accepted["status"] == "LINKED_MATCH", accepted
    code, relocations = object_functions(path)[name]
    assert compare(name, code, relocations)["status"] == "NORMALIZED_MATCH"
    elf = Elf32(path.read_bytes())
    linker = ObjectLinker(path, addresses)
    calls = [r for records in linker.relocations.values() for r in records if r["kind"] == 4]
    called = calls[0]["symbol"]["name"]
    wrong = dict(addresses)
    wrong[called] += 4
    assert compare_object(name, path, linker=ObjectLinker(path, wrong))["status"] == "DIFFERENT", "Wrong called address was accepted"
    missing = dict(addresses)
    del missing[called]
    assert compare_object(name, path, linker=ObjectLinker(path, missing))["status"] == "UNRESOLVED_RELOCATION", "Missing symbol was accepted"
    bad = bytearray(elf.data)
    rel_section = next(s for s in elf.sections if s["type"] == 9 and s["info"] == elf.section(".text")["index"])
    info = struct.unpack_from("<I", bad, rel_section["offset"] + 4)[0]
    struct.pack_into("<I", bad, rel_section["offset"] + 4, (info & ~255) | 9)  # Unsupported GOT16
    altered = ROOT / "build/tests/unsupported_relocation.o"
    altered.parent.mkdir(parents=True, exist_ok=True)
    altered.write_bytes(bad)
    assert compare_object(name, altered)["status"] == "UNRESOLVED_RELOCATION", "Unsupported relocation was accepted"
    ctor_path = ROOT / "build/obj/P2/bis.o"
    compile_source(ROOT / "src/P2/bis.cpp", ctor_path)
    ctor = "__18CBinaryInputStream"
    vtable = "_vt$18CBinaryInputStream"
    assert compare_object(ctor, ctor_path)["status"] == "LINKED_MATCH"
    shifted = dict(addresses)
    shifted[vtable] += 0x8000
    changed = compare_object(ctor, ctor_path, linker=ObjectLinker(ctor_path, shifted))
    assert changed["status"] == "DIFFERENT" and len(changed["differences"]) == 2, "HI16 carry or LO16 operand was ignored"
    raw = bytearray(ctor_path.read_bytes())
    ctor_elf = Elf32(raw)
    ctor_symbols = {(s["table"], s["index"]): s for s in ctor_elf.symbols()}
    changed_low = False
    for section in ctor_elf.sections:
        if section["type"] != 9 or section["info"] != ctor_elf.section(".text")["index"]:
            continue
        for offset in range(section["offset"], section["offset"] + section["size"], 8):
            place, info = struct.unpack_from("<II", raw, offset)
            symbol = ctor_symbols[(section["link"], info >> 8)]
            if symbol["name"] == vtable and info & 255 == 6:
                struct.pack_into("<I", raw, offset + 4, info & ~255)
                changed_low = True
                break
    assert changed_low
    orphan = ROOT / "build/tests/orphan_high.o"
    orphan.write_bytes(raw)
    assert compare_object(ctor, orphan)["status"] == "UNRESOLVED_RELOCATION", "Unpaired HI16 was accepted"
    save_json(ROOT / "build/reports/relocation_validation.json", {"real_object_positive_checks": 2, "wrong_call_rejected": True, "missing_symbol_rejected": True, "unsupported_relocation_rejected": True, "high_low_carry_change_rejected": True, "unpaired_high_rejected": True})
    print("PASS: real relocated calls and HI/LO pairs; five corrupted/unresolved cases rejected")


if __name__ == "__main__":
    main()

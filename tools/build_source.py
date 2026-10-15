"""Rebuild verified C/C++ functions inside the preserved original ELF layout.

This is a partial source build. Remaining code, data, IOP and VU bytes are
preservation inputs, explicitly excluded from source completion counts.
"""
import hashlib
import json
from common import ROOT, target_config, save_json, Elf32
from source_progress import collect


def main():
    target = target_config()
    original = (ROOT / "disc" / target["serial"]).read_bytes()
    if hashlib.sha256(original).hexdigest() != target["sha256"]:
        raise ValueError("Original ELF checksum mismatch")
    patches, progress = collect()
    if progress["failures"]:
        raise SystemExit("Source build refused: fix reported source errors")
    if progress["pending_relocations"]:
        raise SystemExit("Source build refused: resolve pending source relocations")
    rebuilt = bytearray(original)
    elf = Elf32(original)
    covered = set()
    base, file_base, size = (target["text"][key] for key in ("addr", "offset", "size"))
    for patch in patches:
        address, raw = patch["address"], patch["data"]
        offset = file_base + address - base
        if address < base or address + len(raw) > base + size:
            raise ValueError("Source replacement lies outside main EE text")
        region = set(range(offset, offset + len(raw)))
        if covered & region:
            raise ValueError("Overlapping source functions")
        covered.update(region)
        if original[offset:offset + len(raw)] != raw:
            raise ValueError("Source replacement differs from original")
        rebuilt[offset:offset + len(raw)] = raw
    data_covered = set()
    for patch in json.loads((ROOT / 'build/reports/source_data_patches.json').read_text()):
        address, raw = patch['address'], bytes.fromhex(patch['data_hex'])
        section = next((section for section in elf.sections
                        if section['type'] == 1 and section['flags'] & 2 and not section['flags'] & 4
                        and section['addr'] <= address
                        and address + len(raw) <= section['addr'] + section['size']), None)
        if section is None:
            raise ValueError('Source data replacement lies outside initialized data')
        offset = section['offset'] + address - section['addr']
        if original[offset:offset + len(raw)] != raw:
            raise ValueError('Source data replacement differs from original')
        region = set(range(offset, offset + len(raw)))
        if covered & region:
            raise ValueError('Source data overlaps executable code')
        data_covered.update(region)
        rebuilt[offset:offset + len(raw)] = raw
    digest = hashlib.sha256(rebuilt).hexdigest()
    if digest != target["sha256"]:
        raise ValueError("Rebuilt executable differs from original")
    destination = ROOT / "build/SCUS_974.64.source.elf"
    destination.write_bytes(rebuilt)
    save_json(ROOT / "build/reports/source_build.json", {"kind": "partial-C-C++-source-build", "sha256": digest, "expected_sha256": target["sha256"], "match": True, "verified_functions": len(patches), "compiled_code_bytes": len(covered), "compiled_data_bytes": len(data_covered), "preserved_main_text_bytes": size - len(covered), "preserved_other_bytes": len(original) - size - len(data_covered), "full_cpp_relink_complete": False, "note": "Only listed compiled functions and complete matching initialized data count as recovered source. Remaining original executable bytes are preserved."})
    print(f"Built {len(patches)} C/C++ functions into {destination.name}; complete ELF SHA-256 MATCH")


if __name__ == "__main__":
    main()

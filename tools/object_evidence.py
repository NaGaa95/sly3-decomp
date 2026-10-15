"""Record relocation operands and original instructions for address recovery."""
import struct
from common import ROOT, Elf32, target_config


def function_evidence(path, name, address):
    elf = Elf32(path.read_bytes())
    symbols = elf.symbols()
    lookup = {(s["table"], s["index"]): s for s in symbols}
    function = next(s for s in symbols if s["name"] == name and s["type"] == 2)
    raw = elf.section_data(elf.sections[function["shndx"]])
    original = Elf32((ROOT / "disc" / target_config()["serial"]).read_bytes())
    target = original.at_vram(address, function["size"])
    result = []
    for section in elf.sections:
        if section["type"] != 9 or section["info"] != function["shndx"]:
            continue
        for offset in range(section["offset"], section["offset"] + section["size"], section["entsize"] or 8):
            place, info = struct.unpack_from("<II", elf.data, offset)
            if not function["value"] <= place < function["value"] + function["size"]:
                continue
            symbol = lookup[(section["link"], info >> 8)]
            relative = place - function["value"]
            object_word = struct.unpack_from("<I", raw, place)[0]
            target_word = struct.unpack_from("<I", target, relative)[0]
            record = {"instruction": relative // 4, "type": info & 255, "symbol": symbol["name"], "symbol_type": symbol["type"], "symbol_section": symbol["shndx"], "symbol_value": symbol["value"], "target_word": f"0x{target_word:08X}", "object_word": f"0x{object_word:08X}"}
            if info & 255 == 4:
                addend = (object_word & 0x03ffffff) << 2
                if symbol["type"] != 3 and addend & 0x08000000:
                    addend -= 0x10000000
                value = ((target_word & 0x03ffffff) << 2) | ((address + relative + 4) & 0xf0000000)
                record["expected_address"] = f"0x{(value - addend) & 0xffffffff:08X}"
            result.append(record)
    return result

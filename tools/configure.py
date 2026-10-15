"""Derive the Sly 3 target and section map from the verified local executable."""
import csv
import hashlib
import json
import re
import struct
from common import ROOT, Elf32, save_json


def main():
    path = ROOT / "disc/SCUS_974.64"
    data = path.read_bytes()
    elf = Elf32(data)
    sha1 = hashlib.sha1(data).hexdigest()
    target_path = ROOT / "config/target.json"
    if target_path.exists() and json.loads(target_path.read_text())["sha1"] != sha1:
        raise ValueError("Executable changed; inspect the disc version before reconfiguring")
    gp = struct.unpack_from("<6I", elf.section_data(elf.section(".reginfo")))[5]
    text = elf.section(".text")
    target = {"game": "Sly 3: Honor Among Thieves", "region": "USA", "serial": "SCUS_974.64", "sha1": sha1, "sha256": hashlib.sha256(data).hexdigest(), "elf_size": len(data), "entry": elf.entry, "gp": gp, "text": text, "compiler_status": "GCC 2.95.3-136 empirically supported for tested engine and SDK cohorts; per-file profiles in docs/COMPILER.md", "compiler": "tools/third_party/ee-gcc2.95.3-136", "assembler": "tools/third_party/ee-gcc2.95.3-114/lib/gcc-lib/ee/2.95.3/ps2eeas.exe", "cflags": ["-O2", "-G0", "-ffast-math", "-mvu0-use-vf0-vf31", "-fno-exceptions"], "ghidra_language": "r5900:LE:32:default"}
    if target_path.exists():
        previous = json.loads(target_path.read_text())
        for key in ("compiler", "assembler", "cflags"):
            if key in previous:
                target[key] = previous[key]
    save_json(target_path, target)
    save_json(ROOT / "config/sections.json", {"entry": elf.entry, "gp": gp, "elf_flags": elf.flags, "program_headers": elf.program_headers, "sections": elf.sections})
    section_dir = ROOT / "disc/sections"
    section_dir.mkdir(parents=True, exist_ok=True)
    exports = []
    for section in elf.sections:
        if not section["size"] or section["type"] == 8:
            continue
        name = f"{section['index']:02d}_" + re.sub(r"[^A-Za-z0-9_.-]", "_", section["name"]).lstrip(".") + ".bin"
        (section_dir / name).write_bytes(elf.section_data(section))
        exports.append({"section": section["name"], "file": name, "offset": section["offset"], "size": section["size"], "sha256": hashlib.sha256(elf.section_data(section)).hexdigest()})
    save_json(section_dir / "manifest.json", exports)
    irx = elf.section(".irx")
    blob = elf.section_data(irx)
    modules = []
    module_dir = ROOT / "disc/irx"
    module_dir.mkdir(parents=True, exist_ok=True)
    for match in re.finditer(b"\x7fELF", blob):
        start = match.start()
        try:
            module = Elf32(blob[start:])
            end = max([52, module.phoff + module.phentsize * module.phnum, module.shoff + module.shentsize * module.shnum] + [s["offset"] + s["size"] for s in module.sections if s["type"] != 8] + [p["offset"] + p["filesz"] for p in module.program_headers])
            name = f"module_{len(modules):02d}.irx"
            extracted = blob[start:start + end]
            (module_dir / name).write_bytes(extracted)
            strings = re.findall(rb"[\x20-\x7e]{5,}", extracted)
            modules.append({"file": name, "elf_offset": irx["offset"] + start, "size": end, "sha256": hashlib.sha256(extracted).hexdigest(), "strings_preview": [s.decode() for s in strings[:12]]})
        except (ValueError, struct.error, IndexError):
            continue
    save_json(module_dir / "manifest.json", modules)
    symbol_path = ROOT / "config/symbol_addrs.txt"
    if not symbol_path.exists():
        symbol_path.write_text(f"_start = 0x{elf.entry:08X}; // type:func\n", encoding="utf-8")
    for directory in ("src/P2", "src/hand", "src/lib", "include", "notes", "build/hand_wip", "build/reports", "config", "docs"):
        (ROOT / directory).mkdir(parents=True, exist_ok=True)
    print(f"Configured {target['serial']}, entry 0x{elf.entry:X}, gp 0x{gp:X}")
    print(f"Exported {len(exports)} ELF sections and {len(modules)} embedded IOP modules")


if __name__ == "__main__":
    main()

"""Compile and compare individual functions; relocation-normalized matches are provisional."""
import argparse
import csv
import re
import struct
import subprocess
from pathlib import Path
import rabbitizer
from common import ROOT, Elf32, target_config
from compiler import compile_source

rabbitizer.config.regNames_gprAbiNames = rabbitizer.Abi.O32


def functions():
    result = {}
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        for row in csv.DictReader(stream):
            result[row["Name"]] = (int(row["Start"], 16), int(row["End"], 16) - int(row["Start"], 16))
    by_address = {address: size for address, size in result.values()}
    for line in (ROOT / "config/symbol_addrs.txt").read_text().splitlines():
        match = re.match(r"(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if match and int(match[2], 16) in by_address:
            address = int(match[2], 16)
            result[match[1]] = (address, by_address[address])
    return result


def disasm(word, addr):
    return rabbitizer.Instruction(word, vram=addr, category=rabbitizer.InstrCategory.R5900).disassemble()


def words(data):
    if len(data) % 4:
        raise ValueError("Function length is not instruction aligned")
    return list(struct.unpack("<%dI" % (len(data) // 4), data))


def object_functions(path):
    elf = Elf32(Path(path).read_bytes())
    relocations = {}
    for s in elf.sections:
        if s["type"] == 9:
            offsets = relocations.setdefault(s["info"], {})
            for pos in range(s["offset"], s["offset"] + s["size"], 8):
                offset, info = struct.unpack_from("<II", elf.data, pos)
                if offset in offsets:
                    raise ValueError("Multiple relocations at one instruction are unsupported")
                offsets[offset] = info & 255
    result = {}
    for symbol in elf.symbols():
        if symbol["type"] != 2 or not symbol["size"] or symbol["shndx"] >= len(elf.sections):
            continue
        s = elf.sections[symbol["shndx"]]
        start, end = symbol["value"], symbol["value"] + symbol["size"]
        raw = elf.section_data(s)[start:end]
        if len(raw) != symbol["size"]:
            raise ValueError("Object function exceeds its section")
        rel = {(off - start) // 4: kind for off, kind in relocations.get(symbol["shndx"], {}).items() if start <= off < end}
        result[symbol["name"]] = (words(raw), rel)
    return result


def mask(word, kind):
    if kind is None or kind == 0:
        return word
    if kind == 4:
        return word & 0xFC000000
    if kind in (1, 5, 6, 7, 8, 9, 10, 11):
        return word & 0xFFFF0000
    if kind == 2:
        return 0
    raise ValueError(f"Unsupported MIPS relocation {kind}; comparison refused")


def compare(name, compiled, rel, elf=None, known=None):
    known = known if known is not None else functions()
    if name not in known:
        return {"name": name, "status": "UNKNOWN_SYMBOL"}
    addr, size = known[name]
    elf = elf or Elf32((ROOT / "disc" / target_config()["serial"]).read_bytes())
    target = words(elf.at_vram(addr, size))
    # Inferred boundaries include padding; only excess zero words may be removed.
    while len(target) > len(compiled) and target[-1] == 0:
        target.pop()
    length = max(len(target), len(compiled))
    differences = [i for i in range(length) if i >= len(target) or i >= len(compiled) or mask(target[i], rel.get(i)) != mask(compiled[i], rel.get(i))]
    status = "NORMALIZED_MATCH" if not differences and rel else "EXACT_MATCH" if not differences else "DIFFERENT"
    return {"name": name, "address": addr, "status": status, "instructions": len(compiled), "relocations": len(rel), "differences": differences, "target": target, "compiled": compiled}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    target = sub.add_parser("target")
    target.add_argument("name")
    check = sub.add_parser("check")
    check.add_argument("source", type=Path)
    check.add_argument("names", nargs="*")
    args = parser.parse_args()
    if args.command == "target":
        addr, size = functions()[args.name]
        elf = Elf32((ROOT / "disc" / target_config()["serial"]).read_bytes())
        for i, word in enumerate(words(elf.at_vram(addr, size))):
            print(f"{addr + i * 4:08X} {word:08X}  {disasm(word, addr + i * 4)}")
        return
    output = ROOT / "build/obj" / (args.source.name + ".o")
    try:
        compile_source(args.source, output)
    except subprocess.CalledProcessError as error:
        print(error.stdout or "", error.stderr or "")
        raise SystemExit(error.returncode)
    objects = object_functions(output)
    from object_bindings import source_bindings
    from relocate import ObjectLinker, symbol_addresses
    known, addresses = source_bindings(args.source, output, functions(), symbol_addresses())
    linker = ObjectLinker(output, addresses=addresses)
    names = args.names or list(objects)
    if not names:
        raise SystemExit("No non-empty functions found in compiled object")
    failed = False
    for name in names:
        if name not in objects:
            print(name + ": NOT_IN_OBJECT")
            failed = True
            continue
        result = compare_object(name, output, known=known, linker=linker)
        print(f"{name}: {result['status']}")
        if result["status"] not in ("EXACT_MATCH", "LINKED_MATCH"):
            failed = True
        if result.get("reason"):
            print("  " + result["reason"])
        for i in result.get("differences", [])[:40]:
            addr = result["address"] + i * 4
            left = disasm(result["target"][i], addr) if i < len(result["target"]) else "<end>"
            right = disasm(result["compiled"][i], addr) if i < len(result["compiled"]) else "<end>"
            print(f"  {addr:08X}  {left:44} | {right}")
    raise SystemExit(1 if failed else 0)


def compare_object(name, path, elf=None, known=None, linker=None):
    """A definitive code comparison, with every relocation applied first."""
    from relocate import ObjectLinker, RelocationError
    known = known if known is not None else functions()
    if name not in known:
        return {"name": name, "status": "UNKNOWN_SYMBOL"}
    try:
        linker = linker or ObjectLinker(path, target=elf)
        raw, evidence = linker.function(name)
    except RelocationError as error:
        return {"name": name, "address": known[name][0], "status": "UNRESOLVED_RELOCATION", "reason": str(error)}
    result = compare(name, words(raw), {}, elf, known)
    if result["status"] == "EXACT_MATCH" and evidence:
        result["status"] = "LINKED_MATCH"
    result["relocations"] = len(evidence)
    result["relocation_evidence"] = evidence
    result["constant_sections"] = linker.data_matches
    return result


if __name__ == "__main__":
    main()

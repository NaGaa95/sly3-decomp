"""Find additional Sly 2 candidates with relocatable data-address pairs masked.

This is candidate discovery only. Strict relocation-aware compilation remains
mandatory; neither inferred names nor matching instruction shapes count.
"""
import csv
import hashlib
import re
import struct
from collections import defaultdict
from common import ROOT, Elf32
from relocate import sign16


def normalized(raw, elf):
    code = list(struct.unpack("<%dI" % (len(raw) // 4), raw))
    while code and code[-1] == 0:
        code.pop()
    result = [w & 0xfc000000 if w >> 26 in (2, 3) else w for w in code]
    ranges = [(s["addr"], s["addr"] + s["size"]) for s in elf.sections if s["flags"] & 2 and s["size"]]
    for i, word in enumerate(code):
        if word >> 26 != 15:  # LUI
            continue
        register = (word >> 16) & 31
        high = (word & 0xffff) << 16
        for j in range(i + 1, min(i + 25, len(code))):
            instruction = code[j]
            opcode, rs, rt = instruction >> 26, (instruction >> 21) & 31, (instruction >> 16) & 31
            # Direct signed-add/load/store addressing. Ordinary offsets and
            # floating constants stay exact unless the full address is mapped.
            uses_offset = opcode in (8, 9, 24, 25, 26, 27, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 49, 53, 55, 57, 61, 63)
            if uses_offset and rs == register:
                address = (high + sign16(instruction)) & 0xffffffff
                if any(start <= address < end for start, end in ranges):
                    result[i] &= 0xffff0000
                    result[j] &= 0xffff0000
            # Stop at a write to the base register or a caller-clobbering call.
            destination = ((instruction >> 11) & 31) if opcode in (0, 28) else rt
            writes = opcode in (0, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 26, 27, 28, 30, 32, 33, 34, 35, 36, 37, 38, 39, 55)
            if (writes and destination == register) or (opcode == 3 and register in set(range(1, 16)) | {24, 25, 31}):
                break
    return struct.pack("<%dI" % len(result), *result)


def main():
    reference = ROOT / "references/sly2"
    original = Elf32((reference / "disc/SCUS_973.16").read_bytes())
    target = Elf32((ROOT / "disc/SCUS_974.64").read_bytes())
    aliases, sources = {}, defaultdict(list)
    for line in (reference / "config/symbol_addrs.txt").read_text().splitlines():
        match = re.match(r"(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if match:
            aliases[int(match[2], 16)] = match[1]
    for row in csv.DictReader((reference / "config/matched.csv").open()):
        address = int(row["addr"], 16)
        if row["source"] not in sources[address]:
            sources[address].append(row["source"])
    index = defaultdict(list)
    for row in csv.DictReader((reference / "config/functions.csv").open()):
        address, end = int(row["Start"], 16), int(row["End"], 16)
        try:
            raw = original.at_vram(address, end - address)
        except ValueError:
            continue
        key = normalized(raw, original)
        if len(key) < 16:
            continue
        choices = sources[address]
        def priority(source):
            return (0 if source.startswith("src/hand/") else 1 if source.startswith("src/lib/") else 2 if source.startswith("src/P2/") else 3, source)
        source = min(choices, key=priority) if choices else ""
        index[hashlib.sha256(key).digest()].append((row, aliases.get(address, row["Name"]), source, len(key)))
    results = []
    for row in csv.DictReader((ROOT / "config/functions.csv").open()):
        address, end = int(row["Start"], 16), int(row["End"], 16)
        key = hashlib.sha256(normalized(target.at_vram(address, end - address), target)).digest()
        choices = index.get(key, [])
        for old, name, source, size in choices:
            results.append({"Sly3Name": row["Name"], "Sly3Address": row["Start"], "Sly2Name": name, "Sly2Address": old["Start"], "Bytes": size, "Comparison": "jump-and-mapped-data-address-pairs-normalized", "Sly2Source": source, "Ambiguous": len(choices) > 1})
    destination = ROOT / "build/reports/sly2_address_candidates.csv"
    with destination.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=("Sly3Name", "Sly3Address", "Sly2Name", "Sly2Address", "Bytes", "Comparison", "Sly2Source", "Ambiguous"))
        writer.writeheader()
        writer.writerows(results)
    unique = [r for r in results if not r["Ambiguous"] and r["Sly2Source"]]
    print(f"Address-normalized discovery: {len({r['Sly3Name'] for r in results})} target functions; {len(unique)} unambiguous source candidates")


if __name__ == "__main__":
    main()

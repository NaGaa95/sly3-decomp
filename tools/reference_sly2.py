"""Snapshot the supplied Sly 2 sources and suggest cross-game reuse candidates.

Suggestions never become Sly 3 symbols or matched source automatically.
"""
import argparse
import csv
import hashlib
import json
import re
import shutil
import struct
import subprocess
from collections import defaultdict
from pathlib import Path
from common import ROOT, Elf32, save_json

REFERENCE = ROOT / "references/sly2"


def snapshot(source):
    source = source.resolve()
    if not (source / "config/functions.csv").is_file():
        raise ValueError("This is not the expected Sly 2 decompilation repository")
    REFERENCE.mkdir(parents=True, exist_ok=True)
    for name in ("src", "include", "config", "notes", "docs"):
        shutil.copytree(source / name, REFERENCE / name, dirs_exist_ok=True)
    for name in ("README.md", "SETUP.md"):
        shutil.copy2(source / name, REFERENCE / name)
    # Preserve the proven Sly 2 assembly filter as an explicitly labelled baseline.
    shutil.copy2(source / "tools/asfix.py", ROOT / "tools/asfix_sly2.py")
    revision = subprocess.run(["git", "--git-dir=" + str(source / ".git"), "rev-parse", "HEAD"], capture_output=True, text=True, check=True).stdout.strip()
    files = []
    for p in REFERENCE.rglob("*"):
        if p.is_file() and p.name != "provenance.json" and "disc" not in p.relative_to(REFERENCE).parts:
            files.append({"path": p.relative_to(REFERENCE).as_posix(), "sha256": hashlib.sha256(p.read_bytes()).hexdigest()})
    save_json(REFERENCE / "provenance.json", {"source": str(source), "upstream": "https://github.com/Komasia/sly2-decomp", "revision": revision, "files": files})
    save_json(ROOT / "config/reference.json", {"upstream": "https://github.com/Komasia/sly2-decomp", "revision": revision, "asfix_sly2_sha256": hashlib.sha256((ROOT / "tools/asfix_sly2.py").read_bytes()).hexdigest(), "policy": "Reference only; Sly 3 types, symbols, compiler settings and matches require independent validation. No upstream LICENSE file was present in the supplied snapshot."})
    save_json(ROOT / "config/local.json", {"sly2_source": str(source)})
    print(f"Saved {len(files):,} Sly 2 reference files from {revision}")


def normalized(data):
    words = list(struct.unpack("<%dI" % (len(data) // 4), data))
    while words and words[-1] == 0:
        words.pop()
    # Only ignore absolute jump/call destinations. Data addresses stay exact.
    words = [word & 0xFC000000 if word >> 26 in (2, 3) else word for word in words]
    return struct.pack("<%dI" % len(words), *words)


def candidates():
    source_elf = Elf32((REFERENCE / "disc/SCUS_973.16").read_bytes())
    target_elf = Elf32((ROOT / "disc/SCUS_974.64").read_bytes())
    aliases = {}
    for line in (REFERENCE / "config/symbol_addrs.txt").read_text().splitlines():
        m = re.match(r"(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            aliases[int(m[2], 16)] = m[1]
    sources = {}
    with (REFERENCE / "config/matched.csv").open(newline="") as stream:
        for row in csv.DictReader(stream):
            sources[int(row["addr"], 16)] = row["source"]
    index = defaultdict(list)
    with (REFERENCE / "config/functions.csv").open(newline="") as stream:
        for row in csv.DictReader(stream):
            start, end = int(row["Start"], 16), int(row["End"], 16)
            try:
                raw = source_elf.at_vram(start, end - start)
            except ValueError:
                continue
            value = normalized(raw)
            if len(value) >= 16:
                index[hashlib.sha256(value).digest()].append((aliases.get(start, row["Name"]), start, raw, sources.get(start, "")))
    rows = []
    with (ROOT / "config/functions.csv").open(newline="") as stream:
        for row in csv.DictReader(stream):
            start, end = int(row["Start"], 16), int(row["End"], 16)
            raw = target_elf.at_vram(start, end - start)
            value = normalized(raw)
            for name, original_start, original_raw, source in index.get(hashlib.sha256(value).digest(), []):
                rows.append({"Sly3Name": row["Name"], "Sly3Address": row["Start"], "Sly2Name": name, "Sly2Address": f"0x{original_start:08X}", "Bytes": len(value), "Comparison": "exact" if raw == original_raw else "jump-targets-and-padding-normalized", "Sly2Source": source, "Ambiguous": len(index[hashlib.sha256(value).digest()]) > 1})
    path = ROOT / "build/reports/sly2_candidates.csv"
    with path.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=("Sly3Name", "Sly3Address", "Sly2Name", "Sly2Address", "Bytes", "Comparison", "Sly2Source", "Ambiguous"))
        writer.writeheader()
        writer.writerows(rows)
    print(f"Found {len(rows):,} Sly 2 reuse suggestions for {len(set(r['Sly3Name'] for r in rows)):,} Sly 3 functions")
    print("Review build/reports/sly2_candidates.csv; these are not verified Sly 3 source matches")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--snapshot", type=Path)
    args = parser.parse_args()
    if args.snapshot:
        snapshot(args.snapshot)
    else:
        candidates()


if __name__ == "__main__":
    main()

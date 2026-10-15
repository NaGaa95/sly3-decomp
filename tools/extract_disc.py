"""Extract all ISO files, verify the boot executable, and record their hashes."""
import argparse
import hashlib
import json
import re
from pathlib import Path
from common import ROOT, SECTOR, Iso9660, save_json, sha256_file


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("iso", type=Path)
    parser.add_argument("--output", type=Path, default=ROOT / "disc")
    parser.add_argument("--boot", default="SCUS_974.64")
    parser.add_argument("--elf-only", action="store_true")
    parser.add_argument("--sha1", help="Expected executable SHA-1; mismatch is fatal")
    parser.add_argument("--hash-iso", action="store_true")
    args = parser.parse_args()
    iso = Iso9660(args.iso)
    try:
        cnf = next(e for e in iso.entries if e["path"] == "SYSTEM.CNF")
        boot = iso.read_at(cnf["lba"] * SECTOR, cnf["size"]).decode("ascii")
        if not re.search(r"BOOT2\s*=\s*cdrom0:\\" + re.escape(args.boot) + r";1", boot):
            raise ValueError("Disc boot executable does not match " + args.boot)
        exe = next(e for e in iso.entries if e["path"] == args.boot)
        executable_sha1 = hashlib.sha1(iso.read_at(exe["lba"] * SECTOR, exe["size"])).hexdigest()
        expected = args.sha1
        target = ROOT / "config/target.json"
        if not expected and args.boot == "SCUS_974.64" and target.exists():
            expected = json.loads(target.read_text())["sha1"]
        if expected and expected != executable_sha1:
            raise ValueError(f"Wrong executable SHA-1: {executable_sha1}; expected {expected}")
        args.output.mkdir(parents=True, exist_ok=True)
        manifest = {"iso": str(iso.path), "iso_size": iso.size, "sector_size": SECTOR, "volume_id": iso.volume_id, "boot": args.boot, "executable_sha1": executable_sha1, "files": []}
        for entry in iso.entries:
            if args.elf_only and entry["path"] not in (args.boot, "SYSTEM.CNF"):
                continue
            path = args.output / entry["path"]
            path.parent.mkdir(parents=True, exist_ok=True)
            tmp = path.with_name(path.name + ".part")
            digest = hashlib.sha256()
            print(f"Extracting {entry['path']} ({entry['size']:,} bytes)", flush=True)
            iso.stream.seek(entry["lba"] * SECTOR)
            remaining = entry["size"]
            with tmp.open("wb") as output:
                while remaining:
                    data = iso.stream.read(min(remaining, 8 * 1024 * 1024))
                    if not data:
                        raise ValueError("Truncated ISO file")
                    output.write(data)
                    digest.update(data)
                    remaining -= len(data)
            tmp.replace(path)
            manifest["files"].append({**entry, "sha256": digest.hexdigest()})
        if args.hash_iso:
            print("Hashing original ISO", flush=True)
            manifest["iso_sha256"] = sha256_file(iso.path)
        save_json(args.output / "manifest.json", manifest)
        print(f"Extracted {len(manifest['files'])} files; {args.boot} SHA-1 {executable_sha1}")
    finally:
        iso.close()


if __name__ == "__main__":
    main()

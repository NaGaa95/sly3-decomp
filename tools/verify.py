"""Verify original disc extractions, section exports, and the baseline executable."""
import argparse
import hashlib
import json
from common import ROOT, sha256_file, target_config


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--iso", action="store_true", help="Also rehash the complete original ISO")
    args = parser.parse_args()
    manifest = json.loads((ROOT / "disc/manifest.json").read_text())
    for entry in manifest["files"]:
        path = ROOT / "disc" / entry["path"]
        if path.stat().st_size != entry["size"] or sha256_file(path) != entry["sha256"]:
            raise ValueError("Disc extraction mismatch: " + entry["path"])
        print("PASS " + entry["path"], flush=True)
    if args.iso:
        from pathlib import Path
        if sha256_file(Path(manifest["iso"])) != manifest["iso_sha256"]:
            raise ValueError("ISO checksum mismatch")
        print("PASS original ISO", flush=True)
    for entry in json.loads((ROOT / "disc/sections/manifest.json").read_text()):
        if sha256_file(ROOT / "disc/sections" / entry["file"]) != entry["sha256"]:
            raise ValueError("ELF section mismatch: " + entry["section"])
    print("PASS all exported ELF sections")
    baseline = ROOT / "build/SCUS_974.64.baseline.elf"
    if baseline.exists():
        if sha256_file(baseline) != target_config()["sha256"]:
            raise ValueError("Baseline executable mismatch")
        print("PASS reconstructed baseline executable")
    source_build = ROOT / "build/SCUS_974.64.source.elf"
    if source_build.exists():
        if sha256_file(source_build) != target_config()["sha256"]:
            raise ValueError("Source executable mismatch")
        print("PASS partial C/C++ source executable")


if __name__ == "__main__":
    main()

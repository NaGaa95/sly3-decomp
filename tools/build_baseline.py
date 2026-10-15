"""Reassemble all EE text as .word data and rebuild the exact original ELF container.

This is an assembly/data preservation baseline, not a C/C++ re-link. Header,
layout, IOP code and VU overlays remain the original extracted bytes.
"""
import argparse
import hashlib
import json
import struct
import subprocess
from common import ROOT, Elf32, save_json, target_config


def prepare():
    target = target_config()
    data = (ROOT / "disc" / target["serial"]).read_bytes()
    if hashlib.sha256(data).hexdigest() != target["sha256"]:
        raise ValueError("Original ELF checksum mismatch")
    text = target["text"]
    start, end = text["offset"], text["offset"] + text["size"]
    directory = ROOT / "disc/baseline"
    directory.mkdir(parents=True, exist_ok=True)
    (directory / "prefix.bin").write_bytes(data[:start])
    (directory / "suffix.bin").write_bytes(data[end:])
    output = ROOT / "asm/baseline_text.s"
    output.parent.mkdir(exist_ok=True)
    with output.open("w", encoding="ascii") as stream:
        stream.write(".text\n.set noreorder\n.globl sly3_baseline_text\n.ent sly3_baseline_text\nsly3_baseline_text:\n")
        for pos in range(start, end, 32):
            values = struct.unpack("<%dI" % (len(data[pos:min(end, pos + 32)]) // 4), data[pos:min(end, pos + 32)])
            stream.write(".word " + ",".join(f"0x{value:08X}" for value in values) + "\n")
        stream.write(".end sly3_baseline_text\n")
    save_json(directory / "manifest.json", {"sha256": target["sha256"], "size": len(data), "text_offset": start, "text_size": text["size"], "prefix_sha256": hashlib.sha256(data[:start]).hexdigest(), "suffix_sha256": hashlib.sha256(data[end:]).hexdigest()})
    print("Prepared complete assembly/data preservation baseline")


def build():
    target = target_config()
    directory = ROOT / "disc/baseline"
    manifest = json.loads((directory / "manifest.json").read_text())
    output = ROOT / "build/baseline_text.o"
    assembler = ROOT / target["assembler"]
    subprocess.run([str(assembler), "-G0", "-mabi=eabi", "-o", output.as_posix(), (ROOT / "asm/baseline_text.s").as_posix()], cwd=ROOT, check=True, capture_output=True, text=True, timeout=180)
    elf = Elf32(output.read_bytes())
    text = elf.section_data(elf.section(".text"))
    if len(text) != manifest["text_size"]:
        raise ValueError("Assembled .text size differs from original")
    prefix, suffix = (directory / "prefix.bin").read_bytes(), (directory / "suffix.bin").read_bytes()
    if hashlib.sha256(prefix).hexdigest() != manifest["prefix_sha256"] or hashlib.sha256(suffix).hexdigest() != manifest["suffix_sha256"]:
        raise ValueError("Baseline container data checksum mismatch")
    rebuilt = prefix + text + suffix
    digest = hashlib.sha256(rebuilt).hexdigest()
    result = {"kind": "assembly/data-preservation-baseline", "sha256": digest, "expected_sha256": target["sha256"], "size": len(rebuilt), "match": digest == target["sha256"], "note": "Not a C/C++ re-link; original header/data/IOP/VU bytes are preserved."}
    (ROOT / "build/SCUS_974.64.baseline.elf").write_bytes(rebuilt)
    save_json(ROOT / "build/reports/baseline_build.json", result)
    if not result["match"]:
        raise ValueError("Baseline differs from original ELF")
    print(f"Reassembled {len(text):,} EE code bytes; complete ELF SHA-256 MATCH")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--prepare", action="store_true")
    args = parser.parse_args()
    if args.prepare:
        prepare()
    else:
        try:
            build()
        except subprocess.CalledProcessError as error:
            print(error.stdout or "", error.stderr or "")
            raise SystemExit(error.returncode)


if __name__ == "__main__":
    main()

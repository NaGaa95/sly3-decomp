"""Report local preparation status and missing requirements."""
import csv
import importlib.metadata
import json
import platform
import sys
from common import ROOT, target_config, save_json


def main():
    checks = []
    def check(name, good, detail):
        checks.append({"name": name, "ok": bool(good), "detail": detail})
        print(f"{'OK' if good else 'MISSING'} {name}: {detail}")
    check("Python", sys.version_info >= (3, 12), f"{platform.python_version()} {platform.machine()}")
    for package in ("rabbitizer", "spimdisasm", "splat64", "n64img", "m2c"):
        try:
            version = importlib.metadata.version(package)
            check(package, True, version)
        except importlib.metadata.PackageNotFoundError:
            check(package, False, "Run setup.ps1")
    target = target_config()
    for name, path in (("Game executable", ROOT / "disc" / target["serial"]), ("Game archive", ROOT / "disc/SLY3.WAD"), ("Compiler", ROOT / target["compiler"] / "bin/ee-gcc.exe"), ("Assembler", ROOT / target["assembler"]), ("Sly 2 reference", ROOT / "references/sly2/provenance.json"), ("Ghidra project", ROOT / "build/ghidra/Sly3.gpr"), ("Preservation baseline", ROOT / "build/SCUS_974.64.baseline.elf")):
        check(name, path.is_file(), str(path.relative_to(ROOT)))
    try:
        count = sum(1 for _ in csv.DictReader((ROOT / "config/functions.csv").open()))
        check("Function index", count > 0, f"{count:,} provisional EE functions")
    except FileNotFoundError:
        check("Function index", False, "Run disassembly/indexing")
    validation = ROOT / "build/reports/compiler_validation.json"
    check("Compiler validation", validation.exists(), "See build/reports/compiler_validation.json")
    warnings = ["GCC 2.95.3-136 profiles are supported by tested engine/runtime samples; additional cohorts and SDK delay-slot assembler settings remain under investigation.", "SLY3.WAD is extracted intact; its encrypted PS2 asset catalogue still needs format research. SlyTools' WAL unpacker is not a PS2 WAD extractor.", "Function boundaries are inferred except documented manual overrides, not retail debug symbols.", "Complete C/C++ linking, IOP/VU decompilation, and emulator verification remain unfinished."]
    save_json(ROOT / "build/reports/environment.json", {"checks": checks, "remaining_decompilation_work": warnings})
    print("Preparation checks " + ("passed" if all(c["ok"] for c in checks) else "incomplete"))
    raise SystemExit(0 if all(c["ok"] for c in checks) else 1)


if __name__ == "__main__":
    main()

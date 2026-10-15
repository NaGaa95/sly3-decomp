"""PS2 disassembly using spimdisasm directly, without N64 graphics dependencies."""
import argparse
import csv
import re
import subprocess
import sys
from common import ROOT, target_config


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--index-only", action="store_true")
    args = parser.parse_args()
    target = target_config()
    output = ROOT / "asm"
    output.mkdir(exist_ok=True)
    cmd = [sys.executable, "-m", "spimdisasm", "elfObjDisasm", str(ROOT / "disc" / target["serial"]), str(output / "main"), "--instr-category", "r5900", "--compiler", "EEGCC", "--endian", "little", "--abi", "EABI32", "--gp", hex(target["gp"]), "--no-libultra-syms", "--no-ique-syms", "--no-hardware-regs", "--disasm-unknown", "--symbol-addrs", str(ROOT / "config/symbol_addrs.txt"), "--save-context", str(ROOT / "build/reports/spim_context"), "--split-functions", str(output / "nonmatchings"), "--function-info", str(ROOT / "build/reports/spim_functions.csv")]
    if not args.index_only:
        subprocess.run(cmd, cwd=ROOT, check=True)
    # Parse spimdisasm's actual assembly labels and addresses; sizes include alignment
    # until the next discovered function. These boundaries are provisional.
    text_path = next((output / "main").rglob("*.text.s"), None)
    if text_path is None:
        raise RuntimeError("spimdisasm did not emit the main .text assembly")
    text = text_path.read_text(encoding="utf-8")
    functions = []
    pending = None
    for line in text.splitlines():
        match = re.match(r"(?:glabel|dlabel)\s+(\S+)", line)
        if match:
            pending = match[1]
        else:
            label = re.match(r"([A-Za-z_$][\w.$]*):", line)
            if label and not label[1].startswith((".L", "L", "D_")):
                pending = label[1]
        match = re.match(r"\s*/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+", line)
        if pending and match:
            addr = int(match[1], 16)
            if not functions or addr > functions[-1][1]:
                functions.append((pending, addr))
            pending = None
    if not functions:
        raise RuntimeError("No function labels recovered; inspect the generated assembly")
    end = target["text"]["addr"] + target["text"]["size"]
    with (ROOT / "config/functions.csv").open("w", newline="", encoding="utf-8") as stream:
        writer = csv.writer(stream)
        writer.writerow(("Name", "Start", "End", "Size", "BoundarySource"))
        for i, (name, start) in enumerate(functions):
            stop = functions[i + 1][1] if i + 1 < len(functions) else end
            writer.writerow((name, f"0x{start:08X}", f"0x{stop:08X}", stop - start, "spimdisasm-provisional"))
    print(f"Indexed {len(functions):,} provisional functions in config/functions.csv")


if __name__ == "__main__":
    main()

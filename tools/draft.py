"""Generate an m2c draft of one function for manual review (never matched automatically)."""
import argparse
import re
import subprocess
import sys
from pathlib import Path
from common import ROOT
from matchtool import functions


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name")
    args = parser.parse_args()
    files = list((ROOT / "asm/nonmatchings").rglob(args.name + ".s"))
    if not files:
        files = list((ROOT / "asm/splat/nonmatchings").rglob(args.name + ".s"))
    if not files:
        # Ghidra can discover functions inside a larger spimdisasm function.
        # Slice the full disassembly using the combined provisional boundaries.
        known = functions()
        if args.name not in known:
            raise SystemExit("Unknown function " + args.name)
        address, size = known[args.name]
        lines = (ROOT / "asm/splat/text.s").read_text(encoding="utf-8").splitlines()
        first = None
        end = len(lines)
        for i, line in enumerate(lines):
            match = re.match(r"\s*/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+", line)
            if match:
                current = int(match[1], 16)
                if first is None and current >= address:
                    first = i
                if current >= address + size:
                    end = i
                    break
        if first is None:
            raise SystemExit("No original assembly found for " + args.name)
        section = []
        for line in lines[first:end]:
            if re.match(r"\s*(glabel|endlabel|nonmatching|\.align)\b", line):
                continue
            section.append(line)
        assembly = "glabel " + args.name + "\n" + "\n".join(section) + "\n"
    else:
        assembly = files[0].read_text(encoding="utf-8")
    output = ROOT / "build/hand_wip" / (args.name + ".draft.c")
    # Preserve the disassembler's physical register numbers. The selected EE
    # m2c target maps $8..$11 to a4..a7; O32 t0..t3 names would lose four
    # register arguments. Its numeric alias map also recognizes $31 as ra.
    draft_input = ROOT / "build/drafts" / (args.name + ".s")
    draft_input.parent.mkdir(exist_ok=True)
    draft_input.write_text(assembly, encoding="utf-8")
    result = subprocess.run([sys.executable, "-m", "m2c.main", "--target", "mipsee-gcc-c", "--valid-syntax", str(draft_input)], cwd=ROOT, capture_output=True, text=True)
    output.write_text('#include "m2c_prelude.h"\n\n' + result.stdout, encoding="utf-8")
    if result.stderr:
        output.with_suffix(".log").write_text(result.stderr, encoding="utf-8")
    print(output)
    if result.returncode:
        print("m2c could not decode this function; use the prepared Ghidra project for R5900/VU code")
    raise SystemExit(result.returncode)


if __name__ == "__main__":
    main()

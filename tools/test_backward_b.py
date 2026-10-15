"""Native positive match and conservative negative branch-policy checks."""
from pathlib import Path
import os
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))



def _native_numeric_li_controls():
    """Measure one-word signed16 LI slots using the configured SN assembler."""
    import json
    import struct
    import subprocess
    from asfix_backward_b import fix, one_delay_instruction, parsed
    from common import Elf32, target_config

    registers = [number for number in range(32) if number != 1]
    values = (-32768, -1, 0, 1, 32767)
    for value in range(-32768, 32768):
        assert one_delay_instruction(parsed("li $2," + str(value)))
    rejected = (
        "$1,1", "$at,1", "$zero,1", "$sp,1", "$v0,1", "$31,32768",
        "$2,-32769", "$2,65535", "$2,305419896", "$2,0x1", "$2,-0x1",
        "$2,+1", "$2,-0", "$2,01", "$2,1+2", "$2,symbol", "$2,%lo(symbol)",
        "$2,(1)", "$2,1<<2", "$2,1; nop", "$2,1,2", "$32,1", "$-1,1",
        "$$2,1", "$f2,1", "$a4,1", "2,1", "$2,", "$2,1.0",
    )
    for operand in rejected:
        assert not one_delay_instruction(parsed("li " + operand)), operand

    def fixture(number, delay):
        name = "branch_fixture_" + str(number)
        target = "target_" + str(number)
        after = "after_" + str(number)
        local = "$Lbegin_" + str(number)
        text = ("\t.globl " + name + "\n\t.globl " + target +
                "\n\t.globl " + after + "\n\t.ent " + name + "\n" + name +
                ":\n\t.set noreorder\n" + target + ":\n" + local + ":\n")
        # Six ordinary instructions leave the existing short-loop policy first
        # and unchanged; this test exercises only the remaining local branch.
        text += "\taddiu $3,$3,1\n" * 6
        return (text + "\t.set nomacro\n\tb " + local + "\n\t" + delay +
                "\n\t.set macro\n\t.set reorder\n" + after +
                ":\n\t.set noreorder\n\tj $31\n\tnop\n\t.set reorder\n\t.end " + name + "\n")

    cases = [("move", "move $2,$0"), ("nop", "nop")]
    cases += [("li_" + str(number) + "_" + str(value),
               "li $" + str(number) + "," + str(value))
              for number in registers for value in values]
    raw = ("gcc2_compiled.:\n__gnu_compiled_c:\n\t.text\n\t.align 3\n" +
           "".join(fixture(i, delay) for i, (_, delay) in enumerate(cases)))
    fixed, evidence = fix(raw)
    assert evidence["engine_padded_loops"] == 0
    assert len(evidence["pinned_branches"]) == len(cases) == 157
    for operand in rejected:
        unsafe = "gcc2_compiled.:\n\t.text\n" + fixture(0, "li " + operand)
        assert not fix(unsafe)[1]["pinned_branches"], operand

    directory = ROOT / "build/tests/backward_b/numeric_li_controls"
    directory.mkdir(parents=True, exist_ok=True)
    raw_path, source, obj = directory / "controls.raw.s", directory / "controls.s", directory / "controls.o"
    raw_path.write_bytes(raw.encode())
    source.write_bytes(fixed.encode())
    assembler = ROOT / target_config()["assembler"]
    command = [str(assembler), "-G0", "-O2", "-mabi=eabi", "-o", obj.as_posix(), source.as_posix()]
    temp = directory / "TEMP"
    temp.mkdir(exist_ok=True)
    environment = os.environ.copy()
    environment.update({key: str(temp) for key in ("TEMP", "TMP", "TMPDIR")})
    result = subprocess.run(command, cwd=ROOT, env=environment, capture_output=True, timeout=120)
    (directory / "stdout.bin").write_bytes(result.stdout)
    (directory / "stderr.bin").write_bytes(result.stderr)
    (directory / "command.json").write_text(json.dumps({"argv": command, "cwd": str(ROOT),
        "TEMP": str(temp), "returncode": result.returncode}, indent=2) + "\n")
    assert result.returncode == 0, result.stderr
    elf = Elf32(obj.read_bytes())
    sections = [section for section in elf.sections if section["name"] == ".text"]
    assert len(sections) == 1 and sections[0]["type"] == 1 and sections[0]["flags"] == 6
    section = sections[0]
    assert not any(s["size"] for s in elf.sections if s["flags"] & 2 and s["index"] != section["index"])
    assert not any(s["size"] for s in elf.sections if s["type"] == 9)
    symbols = {symbol["name"]: symbol for symbol in elf.symbols()}
    functions = [s for s in elf.symbols() if s["type"] == 2 and s["shndx"]]
    assert len(functions) == len(cases) and section["size"] == 40 * len(cases)
    text = elf.section_data(section)
    for i, (_, delay) in enumerate(cases):
        function, target, after = (symbols["branch_fixture_" + str(i)],
                                  symbols["target_" + str(i)], symbols["after_" + str(i)])
        assert function["shndx"] == section["index"] and function["size"] == 40
        assert function["value"] == i * 40 and target["value"] == function["value"]
        assert after["value"] == function["value"] + 32
        pc = function["value"] + 24
        branch, word = struct.unpack_from("<II", text, pc)
        displacement = (branch & 65535) - 65536
        assert branch >> 16 == 0x1000 and pc + 4 + displacement * 4 == target["value"]
        if delay.startswith("li "):
            register, literal = delay.split()[1].split(",")
            opcode, rs, rt, immediate = word >> 26, (word >> 21) & 31, (word >> 16) & 31, word & 65535
            assert opcode in (9, 13) and rs == 0 and rt == int(register[1:])
            encoded_literal = immediate - 65536 if opcode == 9 and immediate >= 32768 else immediate
            assert encoded_literal == int(literal)
        elif delay == "nop":
            assert word == 0
        else:
            assert word in (0x1021, 0x102D)
    print("157 native backward-branch delay/label controls and signed16 decimal LI guards passed")


def main():
    from asfix_backward_b import fix
    from compiler import compile_source
    from matchtool import compare_object

    source = ROOT / "src/hand/func_00255418.c"
    output = ROOT / "build/tests/backward_b/func_00255418.o"
    old_force = os.environ.get("SLY3_FORCE_COMPILE")
    os.environ["SLY3_FORCE_COMPILE"] = "1"
    try:
        compile_source(source, output)
    finally:
        if old_force is None:
            os.environ.pop("SLY3_FORCE_COMPILE", None)
        else:
            os.environ["SLY3_FORCE_COMPILE"] = old_force
    comparison = compare_object("func_00255418", output)
    assert comparison["status"] == "EXACT_MATCH", comparison
    raw = output.with_suffix(".raw.s").read_text()
    anchor = "\tb\t$L19\n\tmove\t$2,$0"
    assert anchor in raw

    def count(text):
        return len(fix(text)[1]["pinned_branches"])

    assert count(raw) == 1
    assert count(raw.replace(anchor, "\tb\texternal_label\n\tmove\t$2,$0")) == 0
    assert count(raw.replace(anchor, "\tb\t$L23\n\tmove\t$2,$0")) == 0
    assert count(raw.replace(anchor, "\tb\t$L19\n\tli\t$2,0x12345678")) == 0
    assert count(raw.replace(anchor, "\tb\t$L19\n$delay_label:\n\tmove\t$2,$0")) == 0
    assert count(raw.replace(anchor, "\tb\t$L19\n\tmove\t$2,$0\n\t.set noreorder")) == 0
    assert count(raw.replace("$L24:\n", "$L24:\n\t.org 0\n")) == 0
    assert count(raw.replace("$L24:\n", "$L24:\n" + "\tnop\n" * 2000)) == 0
    for opaque in ("#APP\n", "\t.word 0x1000FFFB\n", "\t.space 16\n"):
        try:
            fix(raw.replace("$L24:\n", "$L24:\n" + opaque))
        except ValueError:
            pass
        else:
            raise AssertionError("Opaque input was accepted: " + opaque)
    _native_numeric_li_controls()
    print("Fresh native EXACT_MATCH and 11 branch-policy guard checks passed")


if __name__ == "__main__":
    main()

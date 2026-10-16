"""Pure synthetic guards for scalar three-GPR MULT in the SDK ABI filter."""
import json


def fixture(body="", *, before_save="", after_restore="", call_delay=None):
    registers = [31, 30, 23, 22, 21, 20, 19, 18, 17, 16]
    slots = {number: 144 - 16 * rank for rank, number in enumerate(registers)}
    saves = "\n".join(f"\tsq ${number},{slots[number]}($sp)" for number in registers)
    restores = "\n".join(f"\tlq ${number},{slots[number]}($sp)" for number in registers)
    call = ""
    if call_delay is not None:
        call = "\t.set noreorder\n\t.set nomacro\n\tjal synthetic_helper\n" + call_delay + "\n\t.set macro\n\t.set reorder\n"
    return f"""gcc2_compiled.:
\t.text
\t.ent fixture
fixture:
\t.frame $sp,160,$31
\t.mask 0xc0ff0000,-16
\t.fmask 0x00000000,0
\tsubu $sp,$sp,160
{before_save}
{saves}
{body}
{call}{restores}
{after_restore}
\t.set noreorder
\t.set nomacro
\tjr $31
\taddu $sp,$sp,160
\t.set macro
\t.set reorder
\t.end fixture
"""


def run(fix):
    accepted, rejected = [], []

    def accept(label, text, instruction, *, in_call_delay=False):
        output, evidence = fix(text)
        assert output.splitlines().count(instruction) == 1, label
        assert "\tsq " not in output and "\tlq " not in output, label
        assert evidence["abi"] == "gp64 saves in gp128 slots", label
        assert evidence["functions"][0]["frame"] == 160, label
        assert evidence["functions"][0]["mask"] == "0xC0FF0000", label
        if in_call_delay:
            lines = output.splitlines()
            index = lines.index("\tjal synthetic_helper")
            assert lines[index + 1] == instruction, label
        accepted.append(label)

    def reject(label, text, reason):
        try:
            fix(text)
        except ValueError as error:
            assert reason in str(error), (label, str(error), reason)
            rejected.append({"case": label, "reason": str(error)})
        else:
            raise AssertionError("Unsafe SDK MULT fixture accepted: " + label)

    for lane in range(3):
        for number in range(32):
            operands = ["$4", "$5", "$6"]
            operands[lane] = f"${number}"
            instruction = "\tmult " + ",".join(operands)
            if lane == 0 and number == 29:
                reject("numeric_sp_destination", fixture(instruction), "stack pointer")
            else:
                accept(f"physical_lane{lane}_r{number}", fixture(instruction), instruction)
    aliases = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
               "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "fp", "s8", "ra"]
    for alias in aliases:
        instruction = f"\tmult ${alias},$a0,$v1"
        accept("destination_alias_" + alias, fixture(instruction), instruction)
    instruction = "\tmult $v0,$ra,$sp"
    accept("physical_alias_sources", fixture(instruction), instruction)
    instruction = "\tmult $5,$16,$31"
    accept("preserved_register_sources_are_not_writes", fixture(before_save=instruction), instruction)
    instruction = "\tmult $5,$6,$7"
    accept("genuine_call_delay_preserved", fixture(call_delay=instruction), instruction, in_call_delay=True)

    for operands in ("", "$4", "$4,$5", "$4,$5,$6,$7", "$4,$5,$6,", ",$4,$5", "$4,,$6"):
        reject("bad_arity_" + repr(operands), fixture("\tmult " + operands),
               "exactly three physical GPR operands")
    invalid = ["0", "4", "-1", "0x4", "symbol", "$f0", "$f31", "$f32", "$32", "$99", "$-1", "$+4", "$$4",
               "$s9", "$p0", "$hi", "$lo", "$F0", "$r4", "$a4", "$4+1", "0($4)", "%lo(symbol)", "a0", "$4;", "$4_0", "$"]
    for lane in range(3):
        for value in invalid:
            operands = ["$4", "$5", "$6"]
            operands[lane] = value
            reject(f"invalid_lane{lane}_{value}", fixture("\tmult " + ",".join(operands)),
                   "exactly three physical GPR operands")
    for operands in ("$sp,$4,$5", "$29,$sp,$4", "$sp,$sp,$sp"):
        reject("sp_destination_" + operands, fixture("\tmult " + operands), "SDK")
    for number in (16, 17, 18, 19, 20, 21, 22, 23, 30, 31):
        instruction = f"\tmult ${number},$5,$6"
        reject(f"saved_r{number}_before_save", fixture(before_save=instruction),
               "Saved GPR is written before its save")
        reject(f"saved_r{number}_after_restore", fixture(after_restore=instruction),
               "A return path omits a saved GPR restore")
    for branch in ("beqz", "beqzl"):
        block = f"\t.set noreorder\n\t.set nomacro\n\t{branch} $2,$Lreturn\n\tmult $16,$5,$6\n\t.set macro\n\t.set reorder\n$Lreturn:"
        reject("restored_destination_in_" + branch + "_delay", fixture(after_restore=block),
               "A return path omits a saved GPR restore")
    for mnemonic in ("multu", "mult1", "dmult", "mul"):
        reject("other_mnemonic_" + mnemonic, fixture(f"\t{mnemonic} $4,$5,$6"),
               "Instruction is outside scalar SDK ABI")
    return {"status": "SDK_SCALAR_MULT_PURE_GUARDS_PASS", "accepted": len(accepted),
            "rejected": len(rejected), "positive_cases": accepted, "negative_cases": rejected}


def main():
    from asfix_sdk_gp64 import fix
    result = run(fix)
    print(json.dumps(result, indent=2))
    return result


if __name__ == "__main__":
    main()

"""Move eligible compiler-generated loop-delay updates before the backedge.

Caller must subsequently apply the existing padding filter with loop length7.
This function does not modify global filter settings or read original game code.
"""
import re
from asfix_sly2 import COND, classify, reg

def move_loop_delays(text):
    lines = text.splitlines()
    labels = {}
    for i, line in enumerate(lines):
        parsed = classify(line)
        if parsed[0] == "label": labels[parsed[1]] = i
    out = []
    noreorder = False
    skip = None
    moved = []
    for i, line in enumerate(lines):
        if i == skip: continue
        parsed = classify(line)
        if parsed[0] == "dir":
            if re.match(r"\.set\s+noreorder", parsed[1]): noreorder = True
            elif re.match(r"\.set\s+reorder", parsed[1]): noreorder = False
        if parsed[0] != "insn" or parsed[1] not in COND or not noreorder:
            out.append(line)
            continue
        operands = [item.strip() for item in parsed[2].split(",")]
        target = operands[-1]
        if target not in labels or labels[target] >= i:
            out.append(line)
            continue
        if parsed[1] in ("beql", "bnel", "beqzl", "bnezl", "blezl", "bgtzl", "bltzl", "bgezl", "bc1fl", "bc1tl"):
            raise ValueError("Branch-likely delay updates cannot move onto the untaken path")
        if i+1 >= len(lines): raise ValueError("Loop branch has no delay instruction")
        delay = classify(lines[i+1])
        if delay[0] != "insn": raise ValueError("Loop delay instruction must immediately follow branch")
        if delay[1] == "nop":
            out.append(line)
            continue
        # Only pure integer updates are admitted. Memory operations, calls,
        # trapping arithmetic and opaque macros are refused.
        if delay[1] not in ("addu", "addiu", "daddu", "daddiu", "move"):
            raise ValueError("Unsupported loop delay instruction: " + lines[i+1].strip())
        update_operands = [item.strip() for item in delay[2].split(",")]
        expected_count = 2 if delay[1] == "move" else 3
        if len(update_operands) != expected_count or not update_operands[0].startswith("$"):
            raise ValueError("Unsupported loop delay destination")
        for operand in update_operands[:2]:
            if not operand.startswith("$") or not 0 <= reg(operand) < 32:
                raise ValueError("Loop update is not a general-purpose register operation")
        if expected_count == 3:
            last = update_operands[-1]
            if last.startswith("$"):
                if not 0 <= reg(last) < 32: raise ValueError("Invalid source register")
                if delay[1] in ("addiu", "daddiu"): raise ValueError("Immediate update requires a literal")
            else:
                # Reject expansion through the assembler's temporary register.
                try: immediate = int(last, 0)
                except ValueError: raise ValueError("Loop update immediate must be a literal")
                if not -32768 <= immediate <= 32767:
                    raise ValueError("Loop update may expand to multiple instructions")
        destination = reg(update_operands[0])
        branch_reads = {reg(operand) for operand in operands[:-1] if operand.startswith("$")}
        if destination in branch_reads:
            raise ValueError("Loop delay update writes the branch condition")
        out.extend((lines[i+1], line, "\tnop"))
        skip = i+1
        moved.append({"line": i+1, "branch": line.strip(), "update": lines[i+1].strip()})
    return "\n".join(out) + "\n", moved


def fix(text):
    import types
    import asfix_sly2
    rewritten, moved = move_loop_delays(text)
    # Isolated globals preserve the engine's length6 during parallel builds.
    padding = types.FunctionType(asfix_sly2.fix.__code__, {**asfix_sly2.__dict__, "LOOP_LEN": 7})
    result, count = padding(rewritten)
    return result, {"moved_updates": moved, "padded_loops": count}

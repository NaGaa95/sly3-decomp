"""Preserve compiler-filled backward branch delay slots.

The existing engine policy runs first, unchanged. The remaining compiler-local
backward unconditional branches in explicit noreorder/nomacro scaffolds can be
encoded from their labels and current PC to prevent SN from padding them again.
This module does not read game code, symbol addresses, or comparison results.
"""
import re
from asfix_sly2 import classify, fix as engine_fix, reg


def parsed(line):
    node = classify(line)
    if node[0] == "dir":
        return ("dir", re.sub(r"\s+", " ", node[1]))
    return node


def one_delay_instruction(node):
    # Admit only instruction/operand forms independently proved as one word.
    if node[0] != "insn":
        return False
    if node[1] == "nop":
        return not node[2].strip()
    if node[1] == "move":
        operands = [operand.strip() for operand in node[2].split(",")]
        if len(operands) != 2 or any(not operand.startswith("$") for operand in operands):
            return False
        try:
            return all(0 <= reg(operand) < 32 for operand in operands)
        except (KeyError, ValueError):
            return False
    if node[1] == "li":
        operands = [operand.strip() for operand in node[2].split(",")]
        if len(operands) != 2:
            return False
        destination, literal = operands
        # Match the compiler's numeric GPR and decimal literal spellings only.
        # Reserved assembler temporary $1, named aliases, hex, expressions and
        # multi-word macros stay excluded; SN crashes on the $1 LI controls.
        if not re.fullmatch(r"\$(?:0|[2-9]|[12][0-9]|3[01])", destination):
            return False
        if not re.fullmatch(r"(?:0|-?[1-9][0-9]*)", literal):
            return False
        return -32768 <= int(literal, 10) <= 32767
    return False


def fix(raw):
    if "gcc2_compiled." not in raw or re.search(r"^\s*#(?:APP|NO_APP)\b", raw, re.M):
        raise ValueError("Requires compiler-generated assembly without inline assembly")
    # Opaque raw machine code cannot participate in this proof. Compiler data
    # declarations outside functions are harmless; inside text they are not.
    function = None
    for line in raw.splitlines():
        node = parsed(line)
        if node[0] == "dir" and node[1].startswith(".ent "):
            function = node[1].split()[1]
        elif node[0] == "dir" and node[1].startswith(".end "):
            function = None
        elif function and node[0] == "dir" and re.match(r"\.(word|byte|half|space|skip)\b", node[1]):
            raise ValueError("Opaque code in a compiler function")

    text, padded = engine_fix(raw)
    lines = text.splitlines()
    nodes = [parsed(line) for line in lines]
    labels, contexts = {}, []
    function, noreorder, nomacro = None, False, False
    for i, node in enumerate(nodes):
        if node[0] == "dir":
            if node[1].startswith(".ent "):
                function = node[1].split()[1]
                noreorder = nomacro = False
            elif node[1].startswith(".end "):
                function = None
            elif node[1] == ".set noreorder":
                noreorder = True
            elif node[1] == ".set reorder":
                noreorder = False
            elif node[1] == ".set nomacro":
                nomacro = True
            elif node[1] == ".set macro":
                nomacro = False
        if node[0] == "label":
            if node[1] in labels:
                raise ValueError("Duplicate compiler label")
            labels[node[1]] = (i, function)
        contexts.append((function, noreorder, nomacro))

    pinned = []
    for i, node in enumerate(nodes):
        if node[0] != "insn" or node[1] != "b":
            continue
        target = node[2].strip()
        function, noreorder, nomacro = contexts[i]
        if not function or not noreorder or not nomacro or not re.fullmatch(r"\$L[\w.]+", target):
            continue
        if target not in labels:
            continue
        start, target_function = labels[target]
        if start >= i or function != target_function:
            continue
        # Exactly one non-macro instruction fills the compiler's delay slot,
        # then both modes must close before another label or operation.
        following = [(j, nodes[j]) for j in range(i + 1, len(nodes)) if nodes[j][0] != "blank"][:3]
        if len(following) != 3:
            continue
        delay = following[0][1]
        if not one_delay_instruction(delay):
            continue
        if following[1][1] != ("dir", ".set macro") or following[2][1] != ("dir", ".set reorder"):
            continue

        # Bound encoded distance without pretending to know the assembler's
        # scheduling. Each ordinary instruction is allowed up to 16 words and
        # an additional delay word; conservative alignment adds its full size.
        bound, safe = 1, True
        for j in range(start + 1, i):
            part = nodes[j]
            if contexts[j][0] != function or part[0] == "label+":
                safe = False
                break
            if part[0] == "insn":
                bound += 17
            elif part[0] == "dir":
                value = part[1]
                align = re.fullmatch(r"\.(?:p2align|align)\s+(\d+)", value)
                if align:
                    exponent = int(align[1])
                    if exponent > 8:
                        safe = False
                        break
                    bound += max(0, (1 << exponent) // 4 - 1)
                elif value.startswith(".set "):
                    pass
                elif re.fullmatch(r"\.word\s+0x[0-9A-Fa-f]{8}", value):
                    # Only the engine filter, applied above, may emit these.
                    bound += 1
                else:
                    safe = False
                    break
        if not safe or bound > 32768:
            continue
        indent = re.match(r"^\s*", lines[i]).group(0)
        # The guarded backward displacement is negative: adding it to the
        # opcode plus 0x10000 encodes its signed 16-bit immediate. This avoids
        # SN's historical bitwise-expression parsing differences.
        lines[i] = indent + ".word (0x10010000 + ((" + target + " - . - 4) / 4)) # compiler b " + target
        pinned.append({"function": function, "target_label": target,
                       "compiler_line": i + 1, "conservative_max_backward_words": bound,
                       "compiler_delay_slot": delay[1] + " " + delay[2]})
    return "\n".join(lines) + "\n", {"engine_padded_loops": padded, "pinned_branches": pinned}

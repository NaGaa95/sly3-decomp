"""Fold a compiler conditional around a jump into a branch-likely.

The ordinary conditional's delay always executes; move it before the inverse
condition only if it cannot change that condition. The old unconditional jump
delay then becomes the likely delay, executing only on that same original path.
Only validated register operations and local, bounded targets are eligible.
Never reads original game bytes or resolved function addresses.
"""
import re
from asfix_sly2 import classify, reg, JUMPY, fix as engine_fix


def node(line):
    value = classify(line)
    return ("dir", re.sub(r"\s+", " ", value[1])) if value[0] == "dir" else value


def operands(value):
    return [part.strip() for part in value[2].split(",")]


def number(value):
    if not value.startswith("$"):
        raise ValueError("Not a GPR")
    result = reg(value)
    if not 0 <= result < 32:
        raise ValueError("Not a physical GPR")
    return result


def delay(value, extended=False):
    if value[0] != "insn":
        return None
    args = operands(value)
    if value[1] == "nop" and args == [""]:
        return -1
    if value[1] == "move" and len(args) == 2:
        for arg in args:
            number(arg)
        return number(args[0])
    if value[1] in ("movz", "movn") and len(args) == 3:
        for arg in args:
            number(arg)
        return number(args[0])
    if extended and value[1] in ("addu", "addiu", "daddu", "daddiu") and len(args) == 3:
        number(args[0]); number(args[1])
        amount = int(args[2], 0)
        if -32768 <= amount <= 32767:
            return number(args[0])
    return None


def fix(raw):
    if "gcc2_compiled." not in raw:
        raise ValueError("Compiler marker absent")
    lines = raw.splitlines()
    significant = [(i, node(line)) for i, line in enumerate(lines) if node(line)[0] != "blank"]
    labels, contexts = {}, {}
    function, mode = None, 0
    for i, value in significant:
        if value[0] == "dir" and value[1].startswith(".ent "):
            if function is not None:
                raise ValueError("Nested compiler function")
            function = value[1].split()[1]
        elif value[0] == "dir" and value[1].startswith(".end "):
            if not function or value[1].split()[1] != function or mode:
                raise ValueError("Invalid compiler function end")
            function = None
        elif function and value[0] == "dir" and value[1].startswith(".set "):
            expected = (".set noreorder", ".set nomacro", ".set macro", ".set reorder")
            if value[1] != expected[mode]:
                raise ValueError("Unsupported or nested compiler delay scaffold")
            mode = (mode + 1) % 4
        if value[0] == "label":
            if value[1] in labels:
                raise ValueError("Duplicate label")
            labels[value[1]] = (i, function)
        contexts[i] = function
    if function is not None or mode:
        raise ValueError("Unterminated compiler function or delay scaffold")
    # Inline annotations classify as comments, so inspect them separately.
    protected = set()
    inline = False
    for i, line in enumerate(lines):
        if line.lstrip().startswith("#APP"):
            inline = True
        if inline:
            protected.add(i)
        if line.lstrip().startswith("#NO_APP"):
            inline = False
    if inline:
        raise ValueError("Unterminated inline assembly")
    changes, deleted, folded = {}, set(), []
    opens = [("dir", ".set noreorder"), ("dir", ".set nomacro")]
    closes = [("dir", ".set macro"), ("dir", ".set reorder")]
    for position in range(len(significant) - 12):
        group = significant[position:position + 12]
        indexes, values = zip(*group)
        if list(values[:2]) != opens or list(values[4:6]) != closes:
            continue
        if list(values[6:8]) != opens or list(values[10:12]) != closes:
            continue
        condition, first_delay, jump, second_delay = values[2], values[3], values[8], values[9]
        if condition[0] != "insn" or condition[1] not in ("beq", "bne", "beqz", "bnez"):
            continue
        if jump[0] != "insn" or jump[1] != "b":
            continue
        previous = next((value for _, value in reversed(significant[:position]) if value[0] == "insn"), None)
        if previous and JUMPY.match(previous[1]):
            # Do not expose the moved register operation as a new possible
            # delay filler for a preceding bare compiler branch.
            continue
        if any(i in protected or i in deleted for i in range(indexes[0], indexes[-1] + 1)):
            continue
        args = operands(condition)
        try:
            if len(args) != (2 if condition[1].endswith("z") else 3):
                continue
            read = {number(arg) for arg in args[:-1]}
            written = delay(first_delay)
            if written is None or written in read or delay(second_delay, True) is None:
                continue
        except (ValueError, KeyError):
            continue
        target, exit_label = args[-1], jump[2].strip()
        current = contexts[indexes[2]]
        if not current or any(contexts[i] != current for i in indexes):
            continue
        if target not in labels or exit_label not in labels or labels[exit_label][1] != current:
            continue
        # A conservative bound includes macro expansion and alignment. Refuse
        # unknown directives rather than assume that an inverse branch fits.
        lower, upper = sorted((indexes[2], labels[exit_label][0]))
        bound = 1
        for line_index in range(lower, upper + 1):
            part = node(lines[line_index])
            if part[0] == "insn":
                bound += 17
            elif part[0] == "dir":
                align = re.fullmatch(r"\.(?:p2align|align) ([0-8])", part[1])
                if align:
                    bound += max(0, (1 << int(align[1])) // 4 - 1)
                elif not part[1].startswith(".set "):
                    bound = 32769
                    break
            elif part[0] == "label+" or contexts.get(line_index, current) != current:
                bound = 32769
                break
        if bound > 32768:
            continue
        # The skipped label must be the next meaningful operation, possibly
        # preceded only by alignment. No other entry or instruction may occur.
        after = position + 12
        while after < len(significant) and significant[after][1][0] == "dir" and re.fullmatch(r"\.(?:p2align|align) [0-8]", significant[after][1][1]):
            after += 1
        if after == len(significant) or significant[after][1] != ("label", target):
            continue
        inverse = {"beq": "bnel", "bne": "beql", "beqz": "bnezl", "bnez": "beqzl"}[condition[1]]
        replacement = [lines[indexes[3]], "\t.set noreorder", "\t.set nomacro",
                       "\t" + inverse + " " + ",".join(args[:-1] + [exit_label]),
                       lines[indexes[9]], "\t.set macro", "\t.set reorder"]
        changes[indexes[0]] = replacement
        deleted.update(range(indexes[0], indexes[-1] + 1))
        folded.append({"line": indexes[2] + 1, "condition": condition[1], "inverse": inverse,
                       "skip_label": target, "exit_label": exit_label})
    result = []
    for i, line in enumerate(lines):
        if i in changes:
            result.extend(changes[i])
        elif i not in deleted:
            result.append(line)
    output, engine = engine_fix("\n".join(result) + "\n")
    return output, {"folded_branches": folded, "engine_loops": engine}

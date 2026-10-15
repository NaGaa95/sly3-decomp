"""Conservative assembler choices for recovered SDK memory routines.

Reuse proven signed-immediate literals in registers within a basic block, and
fill bare return slots with their immediately preceding result-register move.
Labels and unknown operations erase literal knowledge. Conditional branch slots
are modeled explicitly, including annulment on branch-likely fallthrough. This
equivalent assembler policy never inspects original game bytes or addresses.
"""
import re
from asfix_sly2 import COND, JUMPY, classify, reg, fix as engine_fix


def fields(node):
    return [item.strip() for item in node[2].split(',')]


def copy_delay_constants(text):
    lines = text.splitlines()
    parsed = [classify(line) for line in lines]
    changes = []
    known, pending, noreorder = {}, None, False
    likely = {'beql', 'bnel', 'beqzl', 'bnezl', 'blezl', 'bgtzl', 'bltzl', 'bgezl', 'bc1fl', 'bc1tl'}
    writes = {'addu', 'addiu', 'daddu', 'daddiu', 'subu', 'dsubu', 'and', 'andi',
              'or', 'ori', 'xor', 'xori', 'nor', 'slt', 'sltu', 'slti', 'sltiu',
              'sll', 'srl', 'sra', 'dsll', 'dsrl', 'dsra', 'dsll32', 'dsrl32',
              'dsra32', 'lw', 'lwu', 'ld', 'lq', 'lh', 'lhu', 'lb', 'lbu',
              'lui', 'mfc1', 'dmfc1', 'mfhi', 'mflo'}
    stores = {'sw', 'sd', 'sq', 'sh', 'sb', 'swc1', 'sdc1', 'nop'}
    for i, node in enumerate(parsed):
        if node[0] in ('label', 'label+'):
            known.clear(); pending = None
            continue
        if node[0] == 'dir':
            if re.fullmatch(r'\.set\s+noreorder', node[1]): noreorder = True
            elif re.fullmatch(r'\.set\s+reorder', node[1]): noreorder = False
            elif not re.match(r'\.(?:set\s+(?:no)?macro|p2align|align)\b', node[1]):
                known.clear(); pending = None
            continue
        if node[0] != 'insn':
            continue
        prior_delay = pending
        pending = None
        operands = fields(node)
        mnemonic = node[1]
        if mnemonic == 'li':
            try:
                destination, literal = reg(operands[0]), int(operands[1], 0)
            except (ValueError, KeyError, IndexError):
                known.clear(); continue
            candidates = [source for source, value in sorted(known.items())
                          if value == literal and 1 < source < 32 and source != destination]
            if 1 < destination < 32 and -32768 <= literal <= 32767:
                if candidates:
                    source = candidates[0]
                    lines[i] = '\tmove\t' + operands[0] + ',$' + str(source)
                    changes.append({'line': i + 1, 'source': source, 'destination': destination, 'literal': literal})
                known[destination] = literal
            else:
                known.pop(destination, None)
        elif mnemonic == 'move':
            destination, source = reg(operands[0]), reg(operands[1])
            if source in known: known[destination] = known[source]
            else: known.pop(destination, None)
        elif mnemonic in COND:
            if noreorder:
                # All supported conditionals leave GPRs untouched. On the
                # fallthrough of likely branches their delay slot is annulled.
                pending = {'kind': 'clear' if mnemonic == 'b' else 'restore' if mnemonic in likely else 'keep', 'before': dict(known)}
            else:
                known.clear()
        elif JUMPY.match(mnemonic):
            if noreorder: pending = {'kind': 'clear', 'before': {}}
            else: known.clear()
        elif mnemonic in writes:
            try: known.pop(reg(operands[0]), None)
            except (KeyError, ValueError, IndexError): known.clear()
        elif mnemonic not in stores:
            known.clear()
        if prior_delay:
            if prior_delay['kind'] == 'clear': known.clear()
            elif prior_delay['kind'] == 'restore': known = prior_delay['before']
    return '\n'.join(lines) + '\n', changes


def fix(text):
    if re.search(r'^\s*#(?:APP|NO_APP)\b', text, re.M) or 'gcc2_compiled.' not in text:
        raise ValueError('Memory assembler policy requires compiler-generated code without inline assembly')
    rewritten, copies = copy_delay_constants(text)
    lines, output_lines, noreorder, returns = rewritten.splitlines(), [], False, 0
    for line in lines:
        node = classify(line)
        if node[0] == 'dir':
            if re.fullmatch(r'\.set\s+noreorder', node[1]): noreorder = True
            elif re.fullmatch(r'\.set\s+reorder', node[1]): noreorder = False
        if node[0] == 'insn' and node[1] in ('j', 'jr') and node[2].strip() in ('$31', '$ra') and not noreorder and output_lines:
            previous = classify(output_lines[-1])
            if previous[0] == 'insn' and previous[1] == 'move' and reg(fields(previous)[0]) == 2:
                result_move = output_lines.pop()
                output_lines.extend(('\t.set\tnoreorder', '\t.set\tnomacro', line, result_move, '\t.set\tmacro', '\t.set\treorder'))
                returns += 1
                continue
        output_lines.append(line)
    rewritten = '\n'.join(output_lines) + '\n'
    output, padding = engine_fix(rewritten)
    return output, {'constant_copies': copies, 'filled_returns': returns, 'padded_loops': padding}

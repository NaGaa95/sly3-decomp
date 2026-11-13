"""Opt-in handling for short loops spanning a compiler 8-byte alignment.

Only inspect a single compiler-generated function with a statically countable,
8-byte-aligned prefix. Refuse ambiguous macros, reorder-mode transfers, and
backedges before the alignment. Other loops use the normal engine policy.
"""
import re
import asfix_sly2 as base


def single_word(node):
    """Accept only the scalar compiler forms whose size is unambiguous here."""
    _, mnemonic, operands = node
    if mnemonic == 'nop':
        return not operands.strip()
    if mnemonic in ('lw', 'sw'):
        return bool(re.fullmatch(r'\s*\$\d+\s*,\s*-?\d+\(\$\d+\)\s*', operands))
    if mnemonic == 'li':
        return bool(re.fullmatch(r'\s*\$\d+\s*,\s*-?\d+\s*', operands)) and not base.multi(mnemonic, operands)
    if mnemonic == 'move':
        return bool(re.fullmatch(r'\s*\$\d+\s*,\s*\$\d+\s*', operands))
    if mnemonic == 'j':
        return operands.strip() == '$31'
    if mnemonic in ('beq', 'bne', 'beql', 'bnel'):
        return bool(re.fullmatch(r'\s*\$\d+\s*,\s*\$\d+\s*,\s*[$\w.]+\s*', operands))
    return False


def harmless_directive(text):
    return bool(re.match(r'\.(?:frame|mask|fmask)\b', text) or
                re.fullmatch(r'\.set\s+(?:noreorder|reorder|nomacro|macro)', text))


def fix(text):
    if re.search(r'^\s*#\s*(?:APP|NO_APP)\b', text, re.M):
        raise ValueError('Inline assembly prevents an exact layout count')
    lines = text.splitlines()
    nodes = [base.classify(line) for line in lines]
    ents = [i for i, n in enumerate(nodes) if n[0] == 'dir' and re.match(r'\.ent\s+', n[1])]
    if len(ents) != 1:
        raise ValueError('Expected exactly one function')
    ent = ents[0]
    text_sections = [i for i, n in enumerate(nodes[:ent]) if n[0] == 'dir' and n[1] == '.text']
    start = text_sections[-1] if text_sections else -1
    if start < 0 or not any(n[0] == 'dir' and re.fullmatch(r'\.align\s+3', n[1]) for n in nodes[start:ent]):
        raise ValueError('Function start must be eight-byte aligned')
    if any(n[0] in ('insn', 'label+') or (n[0] == 'dir' and re.match(r'\.(?:word|byte|half|space|skip)\b', n[1])) for n in nodes[start:ent]):
        raise ValueError('Unexpected text before the aligned function')
    labels = {n[1]: i for i, n in enumerate(nodes) if n[0] == 'label'}
    if len(labels) != sum(n[0] == 'label' for n in nodes):
        raise ValueError('Duplicate labels make the layout ambiguous')
    state = False
    states = []
    for n in nodes:
        if n[0] == 'dir' and re.fullmatch(r'\.set\s+noreorder', n[1]): state = True
        if n[0] == 'dir' and re.fullmatch(r'\.set\s+reorder', n[1]): state = False
        states.append(state)
    changes = []
    for branch, node in enumerate(nodes):
        if node[0] != 'insn' or node[1] not in base.COND or states[branch]: continue
        ops = [x.strip() for x in node[2].split(',')]
        target = labels.get(ops[-1])
        if target is None or target >= branch: continue
        aligns = [j for j in range(target + 1, branch) if nodes[j][0] == 'dir' and re.fullmatch(r'\.p2align\s+3', nodes[j][1])]
        if len(aligns) != 1: continue
        align = aligns[0]
        count = 0
        for j in range(ent + 1, align):
            part = nodes[j]
            if part[0] == 'insn':
                if not single_word(part): raise ValueError('Unknown instruction size in alignment prefix')
                if base.JUMPY.match(part[1]):
                    if not states[j]: raise ValueError('Reorder transfer in alignment prefix')
                    args = [x.strip() for x in part[2].split(',')]
                    if args[-1] in labels and labels[args[-1]] < j: raise ValueError('Earlier backedge may change layout')
                count += 1
            elif part[0] == 'label+':
                raise ValueError('Combined label and instruction')
            elif part[0] == 'dir' and not harmless_directive(part[1]):
                raise ValueError('Unknown alignment prefix directive')
        align_words = count % 2
        body = align_words
        for j in range(target + 1, branch):
            part = nodes[j]
            if j == align: continue
            if part[0] == 'insn':
                if not single_word(part) or (base.JUMPY.match(part[1]) and not states[j]):
                    raise ValueError('Ambiguous loop body')
                body += 1
            elif part[0] == 'label+': raise ValueError('Combined label and instruction')
            elif part[0] == 'dir' and not harmless_directive(part[1]):
                raise ValueError('Ambiguous loop layout')
        pad = base.LOOP_LEN - 2 - body
        if pad <= 0: continue
        indent = re.match(r'^\s*', lines[branch])[0]
        word = base.encode(node[1], ops[:-1], 0)
        replacement = [indent + '.set noreorder'] + [indent + 'nop'] * pad + [
            indent + f'.word 0x{word:08X} | ((({ops[-1]} - . - 4) >> 2) & 0xFFFF)',
            indent + 'nop', indent + '.set reorder']
        changes.append((branch, replacement))
    if len(changes) != 1:
        raise ValueError('Expected one statically countable aligned short loop')
    for i, replacement in reversed(changes): lines[i:i + 1] = replacement
    result, count = base.fix('\n'.join(lines) + '\n')
    return result, {'aligned_loops': len(changes), 'engine_padded_loops': count}

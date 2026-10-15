"""Explicit assembler ordering for a validated, compiler-generated fdlibm cohort.

No original game bytes are inspected. This changes an assembler policy, not C
logic: preserve GCC's scheduled order and explicit delay slots, and retain the
integer-branch interlock represented by its mfc1/#nop pair. Other #nop comments
remain comments. This is deliberately narrower than a general GNU-as clone.
"""
import re
from asfix_sly2 import COND, JUMPY, classify, multi, reg, encode


def fix(text):
    if re.search(r'^\s*#(?:APP|NO_APP)\b', text, re.M):
        raise ValueError('Inline assembly is outside the fdlibm ordering profile')
    if 'gcc2_compiled.' not in text:
        raise ValueError('The fdlibm ordering profile requires GCC-generated assembly')
    lines = text.splitlines()
    parsed = [classify(line) for line in lines]
    label_scopes = {}
    scope_start = None
    for index, node in enumerate(parsed):
        if node[0] == 'dir' and re.match(r'\.ent\b', node[1]): scope_start = index
        if node[0] == 'dir' and re.match(r'\.end\b', node[1]) and scope_start is not None:
            labels = {item[1] for item in parsed[scope_start:index] if item[0] == 'label'}
            for location in range(scope_start, index+1): label_scopes[location] = labels
            scope_start = None
    inside = False
    blocks = []
    closed_blocks = []
    annotations = []
    bare_jumps = set()
    for index, node in enumerate(parsed):
        if node[0] == 'dir' and re.match(r'\.ent\b', node[1]):
            if inside: raise ValueError('Nested assembly function')
            inside = True
            blocks = []
        elif node[0] == 'dir' and re.match(r'\.end\b', node[1]):
            if blocks: raise ValueError('Unterminated explicit delay block')
            inside = False
        elif inside and node[0] == 'dir' and re.match(r'\.set\s+noreorder\s*$', node[1]):
            if blocks: raise ValueError('Nested noreorder block is ambiguous')
            blocks.append({'start': index, 'instructions': [], 'nomacro': False, 'macro': False})
        elif inside and node[0] == 'dir' and re.match(r'\.set\s+nomacro\s*$', node[1]):
            if not blocks or blocks[0]['instructions']: raise ValueError('Unexpected nomacro directive')
            blocks[0]['nomacro'] = True
        elif inside and node[0] == 'dir' and re.match(r'\.set\s+macro\s*$', node[1]):
            if not blocks: raise ValueError('Unexpected macro directive')
            blocks[0]['macro'] = True
        elif inside and node[0] == 'dir' and re.match(r'\.set\s+reorder\s*$', node[1]):
            if not blocks: raise ValueError('Literal reorder block is outside compiler delay scaffolding')
            block = blocks.pop()
            entries = block['instructions']
            if not block['nomacro'] or not block['macro'] or len(entries) != 2:
                raise ValueError('Only GCC control/delay/restore blocks are supported')
            control, delay = (parsed[item] for item in entries)
            if control[1] not in (*COND, 'j', 'jal', 'jr', 'jalr') or multi(control[1], control[2]):
                raise ValueError('The noreorder block is not a compiler branch and delay slot')
            if JUMPY.match(delay[1]) or multi(delay[1], delay[2]) or delay[1] in ('li.s', 'li.d'):
                raise ValueError('The delay slot may expand or contains control flow')
            closed_blocks.append((block['start'], index))
        elif inside and node[0] == 'insn':
            if blocks: blocks[0]['instructions'].append(index)
            elif JUMPY.match(node[1]):
                # GCC can leave controls for assembler scheduling.
                # Pin an empty slot rather than borrowing a preceding operation.
                # A new empty slot preserves their scheduled C instruction
                # order. No following instruction is consumed as a delay.
                operands = [item.strip() for item in node[2].split(',')]
                return_jump = node[1] in ('j', 'jr') and len(operands) == 1 and operands[0].startswith('$') and reg(operands[0]) == 31
                label_jump = node[1] == 'b' and len(operands) == 1 and re.fullmatch(r'[$\w.]+', operands[0])
                conditional = node[1] in COND and node[1] != 'b'
                if not (return_jump or label_jump or conditional): raise ValueError('Control flow lacks an explicit compiler delay slot')
                if label_jump and operands[0] not in label_scopes.get(index, set()):
                    raise ValueError('Unfilled jump target must be a local compiler label')
                if conditional:
                    if not operands or operands[-1] not in label_scopes.get(index, set()): raise ValueError('Unfilled conditional target must be a local compiler label')
                    kind = COND[node[1]][0]
                    count = 3 if kind == 'rs_rt' else 1 if kind == 'cop1' else 2
                    if len(operands) != count: raise ValueError('Invalid conditional operand count')
                    for operand in operands[:-1]:
                        try: number = reg(operand)
                        except (ValueError, KeyError): raise ValueError('Invalid conditional register')
                        if not operand.startswith('$') or not 0 <= number < 32:
                            raise ValueError('Invalid conditional register')
                    try: encode(node[1], operands[:-1], 0)
                    except (KeyError, IndexError, ValueError): raise ValueError('Invalid conditional branch operands')
                bare_jumps.add(index)
        elif inside and node[0] == 'label+':
            raise ValueError('Inline label/instruction syntax is outside the compiler profile')
        elif inside and node[0] == 'label' and blocks:
            raise ValueError('A label occurs inside a delay block')
        elif inside and node[0] == 'dir' and not re.match(r'\.(frame|mask|fmask|p2align|align)\b', node[1]):
            raise ValueError('Unrecognized directive inside a function: ' + node[1])
    if inside: raise ValueError('Unterminated assembly function')
    # The directives above are exclusively verified compiler scaffolding. Their
    # closing reorder restores are replaced, and each function starts in explicit
    # order. Literal/user assembler blocks fail above rather than being changed.
    out = []
    inside = False
    for index, line in enumerate(lines):
        node = parsed[index]
        if node[0] == 'dir' and re.match(r'\.ent\b', node[1]):
            inside = True
            out.append('\t.set\tnoreorder')
        if inside and node[0] == 'dir' and re.match(r'\.set\s+reorder\s*$', node[1]):
            line = re.sub(r'\breorder\b', 'noreorder', line)
        if inside and node[0] == 'insn' and node[1] == 'mfc1':
            operands = [item.strip() for item in node[2].split(',')]
            if len(operands) != 2: raise ValueError('Ambiguous mfc1 operands')
            destination = reg(operands[0])
            if not 0 <= destination < 32 or not re.fullmatch(r'\$f(?:[0-9]|[12][0-9]|3[01])', operands[1]):
                raise ValueError('Invalid mfc1 register operands')
            next_index = index + 1
            while next_index < len(lines) and parsed[next_index][0] in ('blank', 'dir'):
                if parsed[next_index][0] == 'dir' and not re.match(r'\.set\s+(?:no)?(?:reorder|macro)\s*$', parsed[next_index][1]):
                    break
                next_index += 1
            following = parsed[next_index] if next_index < len(lines) else ('blank',)
            if following[0] == 'insn' and following[1] in COND:
                read_operands = [item.strip() for item in following[2].split(',')][:-1]
                readers = {reg(item) for item in read_operands if item.startswith('$')}
                if destination in readers:
                    if index + 1 >= len(lines) or not re.fullmatch(r'\s*#nop\s*', lines[index+1]):
                        raise ValueError('Dependent mfc1 branch lacks the compiler interlock annotation')
                    annotations.append(index + 1)
        if index in annotations:
            line = re.sub(r'#nop', 'nop', line)
        if inside and node[0] == 'insn' and node[1] in ('bc1f','bc1t','bc1fl','bc1tl'):
            operands=[item.strip() for item in node[2].split(',')]
            if len(operands)!=1 or not re.fullmatch(r'[$\w.]+',operands[0]): raise ValueError('Ambiguous FPU branch target')
            if operands[0] not in label_scopes.get(index,set()): raise ValueError('FPU branch target must be a local compiler label')
            line='\t.word 0x%08X | (((%s - . - 4) / 4) & 0xFFFF)' % (encode(node[1],[],0),operands[0])
        out.append(line)
        if index in bare_jumps:
            out.append('\tnop')
        if node[0] == 'dir' and re.match(r'\.end\b', node[1]):
            inside = False
            out.append('\t.set\treorder')
    return '\n'.join(out) + '\n', len(annotations)

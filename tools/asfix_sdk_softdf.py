"""Explicit GNU-ee-2.9 numeric-literal policy for scalar soft-double SDK code.

This selected profile receives compiler assembly only, never game bytes. Supported
integer masks and exact positive powers of two are lowered to ordinary scalar
instructions before the existing SDK64 frame/CFG/delay audit. Other literal
shapes fail closed. The policy is checked against the installed GNU assembler.
"""
import math
import re
import struct
from asfix_sly2 import classify, reg
from asfix_sdk_gp64 import fix as sdk64

def lower_literal(mn, operands):
    args = [part.strip() for part in operands.split(',')]
    if len(args) != 2 or not args[0].startswith('$'):
        raise ValueError('Ambiguous SDK numeric literal')
    try:
        number = reg(args[0])
    except (KeyError, ValueError):
        raise ValueError('SDK literal destination is not a physical GPR')
    if not 0 < number < 32:
        raise ValueError('SDK literal destination must be a writable GPR')
    destination = '$' + str(number)
    if mn == 'dli':
        if not re.fullmatch(r'-?(?:0x[0-9A-Fa-f]+|[0-9]+)', args[1]):
            raise ValueError('SDK dli requires a constant integer')
        value = int(args[1], 0)
        if not -(1 << 63) <= value < (1 << 64):
            raise ValueError('SDK dli exceeds 64 bits')
        if -0x8000 <= value < 0x8000:
            return [f'\taddiu {destination},$0,{value}']
        if 0 <= value < 0x10000:
            return [f'\tori {destination},$0,{value}']
        unsigned = value & ((1 << 64) - 1)
        if unsigned == 0xFFFFFFFF:
            return [f'\tlui {destination},0xFFFF', f'\tdsrl {destination},{destination},32']
        signed = unsigned if unsigned < (1 << 63) else unsigned - (1 << 64)
        if -0x8000 <= signed < 0x8000:
            return [f'\taddiu {destination},$0,{signed}']
        if -(1 << 31) <= signed < 0 and not (unsigned & 0xFFFF):
            return [f'\tlui {destination},{(unsigned >> 16) & 0xFFFF}']
        trailing = (unsigned & -unsigned).bit_length() - 1
        field = unsigned >> trailing
        # These are compiler-generated wide mask literals, not arbitrary
        # numeric material whose assembler synthesis has yet been established.
        width = field.bit_length()
        if width <= 32 or field != (1 << width) - 1:
            raise ValueError('Unsupported SDK integer literal shape')
        leading = 64 - width - trailing
        output = [f'\taddiu {destination},$0,-1']
        if trailing:
            output.append(f'\tdsll {destination},{destination},{leading + trailing}')
        if leading:
            output.append(f'\tdsrl {destination},{destination},{leading}')
        return output
    if mn != 'li.d' or not re.fullmatch(r'[+]?\d+(?:\.\d*)?(?:[eE][+-]?\d+)?', args[1]):
        raise ValueError('SDK double literal must be numeric')
    value = float(args[1])
    if not math.isfinite(value) or value <= 0 or math.frexp(value)[0] != 0.5:
        raise ValueError('Only exact positive double powers of two are admitted')
    bits = struct.unpack('<Q', struct.pack('<d', value))[0]
    if not 1 <= (bits >> 52) & 0x7FF <= 2046:
        raise ValueError('Subnormal double literals are outside this SDK cohort')
    shift = max(0, bits.bit_length() - 16)
    if shift > 63 or bits & ((1 << shift) - 1):
        raise ValueError('The double literal is outside the established two-instruction policy')
    output = [f'\tori {destination},$0,{bits >> shift}']
    if shift:
        output.append(f'\tdsll {destination},{destination},{shift}')
    return output

def canonical_call_slots(lines):
    """Put independent two-GPR soft-double setup in the SDK's argument order.

    Both instructions execute before the callee. Neither reads either argument
    register or the JAL link register, or changes an address/control operand,
    and every other instruction
    and explicit compiler delay block remains at its original position.
    """
    parsed = [classify(line) for line in lines]
    changes = {}
    evidence = []
    for start, node in enumerate(parsed):
        if node[0] != 'dir' or not re.fullmatch(r'\.set\s+noreorder', node[1]):
            continue
        end = start + 1
        instructions = []
        while end < len(parsed):
            entry = parsed[end]
            if entry[0] == 'dir' and re.fullmatch(r'\.set\s+reorder', entry[1]):
                break
            if entry[0] == 'insn':
                instructions.append(end)
            end += 1
        # The complete SDK64 validator has already admitted only paired GCC
        # noreorder/nomacro scaffolds; this scan cannot bless another shape.
        if end == len(parsed) or len(instructions) != 2:
            continue
        call, delay = instructions
        cn, dn = parsed[call], parsed[delay]
        if cn[1] != 'jal' or cn[2].strip() not in ('dpmul', 'dpadd', 'dpsub', 'dpdiv'):
            continue
        preceding = start - 1
        while preceding >= 0 and parsed[preceding][0] == 'blank':
            preceding -= 1
        if preceding < 0:
            continue
        pn = parsed[preceding]
        if pn[0] != 'insn' or pn[1] != 'move' or dn[1] != 'move':
            continue
        operands = []
        for candidate in (pn, dn):
            parts = [part.strip() for part in candidate[2].split(',')]
            if len(parts) != 2 or any(not part.startswith('$') for part in parts):
                raise ValueError('Ambiguous SDK argument move')
            try:
                numbers = [reg(part) for part in parts]
            except (KeyError, ValueError):
                raise ValueError('Invalid SDK argument register')
            if any(not 0 <= number < 32 for number in numbers):
                raise ValueError('SDK argument register exceeds physical registers')
            operands.append(numbers)
        (pd, ps), (dd, ds) = operands
        if pd != 4 or dd != 5:
            continue
        if ps in (4, 5, 31) or ds in (4, 5, 31):
            raise ValueError('SDK call moves have an argument/link-register dependency')
        changes[preceding] = lines[delay]
        changes[delay] = lines[preceding]
        evidence.append({'callee': cn[2].strip(), 'before': lines[preceding].strip(),
                         'delay': lines[delay].strip(), 'source_registers': [ps, ds],
                         'rule': 'independent A1 setup before call; A0 setup in compiler delay'})
    return [changes.get(index, line) for index, line in enumerate(lines)], evidence

def fix(text):
    # Existing SDK64 validation verifies compiler provenance, labels, explicit
    # delay blocks, nonoverlapping frame slots and dominating saves/restores.
    # Lowering before that audit ensures multi-instruction literals in delay
    # slots cannot bypass its exact-two-instruction block rule.
    out = []
    evidence = []
    for line in text.splitlines():
        node = classify(line)
        if node[0] == 'insn' and node[1] in ('dli', 'li.d'):
            lowered = lower_literal(node[1], node[2])
            out.extend(lowered)
            evidence.append({'literal': line.strip(), 'expanded': [item.strip() for item in lowered]})
        else:
            out.append(line)
    # Validate the untouched lowered function first, then the revised complete
    # function again. No failed frame/control/ABI audit is weakened or skipped.
    sdk64('\n'.join(out) + '\n')
    out, calls = canonical_call_slots(out)
    result, proof = sdk64('\n'.join(out) + '\n')
    return result, {'literal_policy': 'GNU assembler 2.9-ee scalar masks and exact soft-double powers',
                    'literals': evidence, 'call_slots': calls, 'sdk64': proof}

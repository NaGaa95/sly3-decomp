"""Opt-in engine-divfix1 profile: one hazard nop before a divide at block position 1.

The engine filter (asfix_sly2.divfix) inserts two nops before div.s/sqrt.s/rsqrt.s/vdiv/vsqrt/vrsqrt when the
instruction starts a basic block. Sly 2's finished decomp (tools/asfix.py there) also inserts one nop when the
divide is the second instruction of its block; that was verified on all 11 such sites in SCUS_973.16.

In Sly 3 this second rule is NOT global: several matched library functions (0x24xxxx/0x28xxxx) have a divide at
position 1 with no nop. Engine functions that do have the nop (e.g. func_00120080, func_00120C80) opt in with
`// SLY3_ASFIX: engine-divfix1`. No original ELF or target words are read.
"""
import re
import asfix_sly2
from asfix_sly2 import classify, BR, DIVOPS


def isize(mn, ops):
    """Machine instructions a (possibly macro) instruction expands to (same rule as Sly 2's tools/asfix.py)."""
    import struct
    if mn == 'li.s':
        try:
            bits = struct.unpack('<I', struct.pack('<f', float(ops.split(',')[1])))[0]
        except Exception:
            return 3
        if bits == 0: return 1
        return 2 if (bits & 0xFFFF) == 0 else 3
    if mn == 'li':
        try: v = int(ops.split(',')[1].strip(), 0)
        except Exception: return 2
        return 1 if (-0x8000 <= v < 0x10000 or ((v & 0xFFFF) == 0 and -0x80000000 <= v < 0x80000000)) else 2
    if mn in ('la', 'dla'): return 2
    return 1


def divfix1(text):
    out = []
    st = False
    pos = 0
    pending = 0
    prev = None
    for l in text.split('\n'):
        c = classify(l)
        if c[0] == 'dir':
            if re.match(r'\.set\s+noreorder', c[1]): st = True
            elif re.match(r'\.set\s+reorder', c[1]): st = False
            elif re.match(r'\.ent\b', c[1]): pos = 0; pending = 0
            out.append(l); continue
        if c[0] == 'label':
            pos = 0; pending = 0; out.append(l); continue
        if c[0] == 'label+':
            pos = 0; pending = 0
            parts = c[2].split(None, 1)
            c = ('insn',) + tuple(parts) + (('',) if len(parts) == 1 else ())
        if c[0] != 'insn':
            out.append(l); continue
        mn = c[1]
        if pos == 1 and DIVOPS.match(mn) and prev != 'nop':
            out.append((re.match(r'^\s*', l).group(0) or '\t') + 'nop')
            pos = 2
        out.append(l)
        prev = mn
        if pending:
            pending = 0; pos = 0
        elif BR.match(mn):
            if st: pending = 1; pos += 1
            else: pos = 0
        else:
            pos += isize(mn, c[2] if len(c) > 2 else '')
    return '\n'.join(out)


def fix(text):
    out, count = asfix_sly2.fix(text)
    return divfix1(out), count

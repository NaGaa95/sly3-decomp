"""Exercise aligned-loop filter using the native EE assembler."""
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from asfix_aligned_loops import fix
from common import Elf32, target_config

RAW = '''\
\t.text
\t.align 3
\t.globl aligned_loop_fixture
\t.globl return_one
\t.globl aligned_head
\t.ent aligned_loop_fixture
aligned_loop_fixture:
\tlw $2,24($4)
\t.set noreorder
\tbnel $2,$5,advance
\tlw $3,56($4)
\t.set reorder
return_one:
\t.set noreorder
\tj $31
\tli $2,1
\t.set reorder
\t.p2align 3
aligned_head:
\tbeq $2,$5,return_one
\tlw $3,4($3)
advance:
\tbeq $3,$0,exit
\tlw $2,16($3)
\t.set noreorder
\tbeql $2,$4,aligned_head
\tlw $2,8($3)
\t.set reorder
exit:
\t.set noreorder
\tj $31
\tmove $2,$0
\t.set reorder
\t.end aligned_loop_fixture
'''


def main():
    fixed, evidence = fix(RAW)
    assert evidence['aligned_loops'] == 1
    directory = ROOT / 'build/tests/asfix_aligned_loops'
    directory.mkdir(parents=True, exist_ok=True)
    assembly, obj = directory / 'fixture.s', directory / 'fixture.o'
    assembly.write_text(fixed)
    command = [str(ROOT / target_config()['assembler']), '-G0', '-O2', '-mabi=eabi', '-o', str(obj), str(assembly)]
    subprocess.run(command, cwd=ROOT, check=True, capture_output=True, timeout=120)
    elf = Elf32(obj.read_bytes())
    text = elf.section_data(elf.section('.text'))
    syms = {s['name']: s for s in elf.symbols()}
    start = syms['aligned_loop_fixture']['value']
    assert syms['return_one']['value'] - start == 12
    assert syms['aligned_head']['value'] - start == 24
    assert syms['aligned_loop_fixture']['size'] == 68
    def word(offset): return struct.unpack_from('<I', text, start + offset)[0]
    assert word(20) == 0 and word(24) == 0
    assert word(28) == base_branch(2, 5, -5)
    assert word(32) == 0
    assert word(52) == ((20 << 26) | (2 << 21) | (4 << 16) | (0xfff8))

    # With an even-length prefix, the alignment directive contributes no NOP.
    # The short-loop policy must add the other padding word after the label.
    even, _ = fix(RAW.replace('return_one:\n', '\tnop\nreturn_one:\n'))
    even_assembly, even_obj = directory / 'even.s', directory / 'even.o'
    even_assembly.write_text(even)
    command[-3:] = ['-o', str(even_obj), str(even_assembly)]
    subprocess.run(command, cwd=ROOT, check=True, capture_output=True, timeout=120)
    elf = Elf32(even_obj.read_bytes())
    text = elf.section_data(elf.section('.text'))
    syms = {s['name']: s for s in elf.symbols()}
    start = syms['aligned_loop_fixture']['value']
    assert syms['return_one']['value'] - start == 16
    assert syms['aligned_head']['value'] - start == 24
    assert syms['aligned_loop_fixture']['size'] == 72
    assert word(24) == 0 and word(28) == 0
    assert word(32) == base_branch(2, 5, -5)
    assert word(36) == 0

    for bad in (RAW.replace('.align 3', '.align 2'),
                RAW.replace('\tlw $2,24($4)', '\tla $2,unknown'),
                RAW.replace('\tlw $2,24($4)', '\tli.s $f0,1.0'),
                RAW.replace('\tlw $2,24($4)', '\tli $2,65537'),
                RAW.replace('\tlw $2,24($4)', '\tmove $2,1'),
                RAW.replace('\tlw $2,24($4)', '\tlw $2,global'),
                RAW.replace('\t.p2align 3', '\t.space 4\n\t.p2align 3'),
                RAW.replace('return_one:', 'return_one:\nreturn_one:')):
        try: fix(bad)
        except ValueError: continue
        raise AssertionError('Ambiguous layout was accepted')
    print('Aligned loop bytes, branch targets and conservative guards passed')


def base_branch(rs, rt, offset):
    return (4 << 26) | (rs << 21) | (rt << 16) | (offset & 0xffff)


if __name__ == '__main__': main()

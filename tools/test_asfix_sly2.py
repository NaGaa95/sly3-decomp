from pathlib import Path
import json
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def main(fix=None, output_name='shared_backedges'):
    sys.path.insert(0, str(ROOT / 'tools'))
    from common import Elf32, target_config
    from asfix_sly2 import COND, encode
    if fix is None:
        from asfix_sly2 import fix

    cases = []
    for mnemonic, (kind, _) in COND.items():
        operands = ['$2', '$3'] if kind == 'rs_rt' else ['$2'] if kind in ('rs', 'regimm', 'z') else []
        cases.append((mnemonic, operands))
    pieces = ['\t.text\n\t.align 3\n']
    for i, (mnemonic, operands) in enumerate(cases):
        name, target = 'branch_fixture_' + str(i), 'shared_target_' + str(i)
        branch = mnemonic + ' ' + ','.join([*operands, target])
        pieces.append('\t.globl ' + name + '\n\t.globl ' + target + '\n\t.ent ' + name + '\n' + name + ':\n\t.set noreorder\n' + target + ':\n\taddiu $4,$4,1\n\t' + branch + '\n\tnop\n\t' + branch + '\n\tnop\n\tjr $31\n\tnop\n\t.set reorder\n\t.end ' + name + '\n\t.align 3\n')
    raw = ''.join(pieces)
    fixed, changed = fix(raw)
    assert changed == len(cases) * 2
    directory = ROOT / 'build/tests/asfix_sly2' / output_name
    directory.mkdir(parents=True, exist_ok=True)
    assembly, obj = directory / 'controls.s', directory / 'controls.o'
    (directory / 'controls.raw.s').write_bytes(raw.encode())
    assembly.write_bytes(fixed.encode())
    argv = [str(ROOT / target_config()['assembler']), '-G0', '-O2', '-mabi=eabi', '-o', obj.as_posix(), assembly.as_posix()]
    job = subprocess.run(argv, cwd=ROOT, capture_output=True, timeout=120)
    (directory / 'stdout.bin').write_bytes(job.stdout)
    (directory / 'stderr.bin').write_bytes(job.stderr)
    (directory / 'command.json').write_text(json.dumps(dict(argv=argv, returncode=job.returncode), indent=2) + '\n')
    assert job.returncode == 0, job.stderr
    elf = Elf32(obj.read_bytes())
    section = elf.section('.text')
    words = elf.section_data(section)
    symbols = {s['name']: s for s in elf.symbols()}
    assert not any(s['size'] for s in elf.sections if s['type'] == 9)
    assert not any(s['size'] for s in elf.sections if s['flags'] & 2 and s['index'] != section['index'])
    for i, (mnemonic, operands) in enumerate(cases):
        function = symbols['branch_fixture_' + str(i)]
        target = symbols['shared_target_' + str(i)]
        assert function['size'] == 44 and target['value'] == function['value']
        positions = []
        for pc in range(function['value'], function['value'] + function['size'], 4):
            word, = struct.unpack_from('<I', words, pc)
            if word & 0xFFFF0000 != encode(mnemonic, operands, 0):
                continue
            offset = (word & 65535) - 65536 if word & 32768 else word & 65535
            assert pc + 4 + offset * 4 == target['value'], (mnemonic, pc, offset)
            positions.append(pc)
        assert positions == [function['value'] + 16, function['value'] + 28], (mnemonic, positions)
    guarded = [
        '\t.text\n\t.set noreorder\nL:\n\tla $2,unknown\n\tbne $2,$0,L\n\tnop\n',
        '\t.text\n\t.set noreorder\nL:\n\t.space 16\n\tbne $2,$0,L\n\tnop\n',
        '\t.text\n\t.set noreorder\n\tbne $2,$0,external_target\n\tnop\n',
        '\t.text\n\t.set noreorder\n\tbne $2,$0,L\n\tnop\nL:\n\tnop\n',
    ]
    for text in guarded:
        assert fix(text)[1] == 0
    print(str(len(cases) * 2) + ' native shared-backedge targets and four conservative guards passed')


if __name__ == '__main__':
    main()

"""Native/state regression proof for the explicit early-exit loop profile.

No game instructions enter the adapter. Native assembler fixtures establish its
empty-slot precondition; instruction execution tests compare the independently
assembled baseline and proposed objects, including every scalar register and
memory access. This test recompiles its ordinary C fixture through the production driver,
then independently checks the source-derived policy with both native assemblers.
"""
import hashlib
import json
import random
import os
from unittest.mock import patch
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'tools'), str(Path(__file__).parent)]
from asfix_engine_exit_slots import fix, materialize
from common import Elf32, target_config
from compiler import compile_source, source_signature, file_hash
from matchtool import compare_object, functions
from relocate import ObjectLinker, symbol_addresses

OUT = ROOT / 'build/tests/engine_exit_slots'
OUT.mkdir(parents=True, exist_ok=True)
MASK = (1 << 64) - 1


def sha(value):
    return hashlib.sha256(value).hexdigest()


def assemble(name, text, profile='sn'):
    path = OUT / (name + '_' + profile + '.s')
    path.write_text(text)
    assembler = ROOT / (target_config()['assembler'] if profile == 'sn' else
                        'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe')
    output = path.with_suffix('.o')
    subprocess.run([str(assembler), '-G0', '-O2', '-mabi=eabi', '-o', str(output), str(path)],
                   cwd=ROOT, check=True, capture_output=True, text=True, timeout=120)
    elf = Elf32(output.read_bytes())
    payload = elf.section_data(elf.section('.text'))
    assert not [s for s in elf.sections if s['type'] in (4, 9) and s['size']]
    assert not [s for s in elf.sections if s['flags'] & 2 and not s['flags'] & 4
                and s['type'] != 8 and s['size']]
    return output, list(struct.unpack('<' + str(len(payload) // 4) + 'I', payload))


def sext(value, bits):
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


def execute(words, incoming, memory):
    """Scalar MIPS subset, architectural branch delay slots and 64-bit GPRs.

    The tested transformations add only NOPs; the access trace also proves that
    no potentially trapping load or store changes its execution path or order.
    Full upper128-bit lane semantics are unnecessary because no moved scalar
    instruction or new non-NOP operation is admitted by this adapter.
    """
    regs = list(incoming)
    regs[0] = 0
    pc, steps, reads, writes = 0, 0, [], []
    memory = dict(memory)

    def plain(word):
        op, rs, rt = word >> 26, (word >> 21) & 31, (word >> 16) & 31
        rd, sh, fn = (word >> 11) & 31, (word >> 6) & 31, word & 63
        imm = word & 65535
        if word == 0:
            return
        if op == 0 and fn in (0x21, 0x2D):
            result = (regs[rs] + regs[rt]) & MASK
            regs[rd] = (sext(result & 0xFFFFFFFF, 32) & MASK) if fn == 0x21 else result
        elif op == 0 and fn in (0x24, 0x25, 0x26, 0x27):
            regs[rd] = ({0x24: lambda a, b: a & b, 0x25: lambda a, b: a | b,
                         0x26: lambda a, b: a ^ b, 0x27: lambda a, b: ~(a | b)}[fn]
                        (regs[rs], regs[rt])) & MASK
        elif op in (9, 25):
            result = (regs[rs] + sext(imm, 16)) & MASK
            regs[rt] = (sext(result & 0xFFFFFFFF, 32) & MASK) if op == 9 else result
        elif op in (12, 13, 14):
            regs[rt] = {12: lambda: regs[rs] & imm, 13: lambda: regs[rs] | imm,
                        14: lambda: regs[rs] ^ imm}[op]() & MASK
        elif op == 15:
            regs[rt] = sext(imm << 16, 32) & MASK
        elif op in (32, 33, 35, 36, 37, 39, 55):
            size = {32: 1, 33: 2, 35: 4, 36: 1, 37: 2, 39: 4, 55: 8}[op]
            address = (regs[rs] + sext(imm, 16)) & 0xFFFFFFFF
            assert address % size == 0
            value = sum(memory[address + n] << (8 * n) for n in range(size))
            reads.append((address, size, value))
            regs[rt] = (sext(value, size * 8) if op in (32, 33, 35) else value) & MASK
        elif op in (40, 41, 43, 63):
            size = {40: 1, 41: 2, 43: 4, 63: 8}[op]
            address = (regs[rs] + sext(imm, 16)) & 0xFFFFFFFF
            assert address % size == 0
            for n in range(size):
                memory[address + n] = (regs[rt] >> (8 * n)) & 255
            writes.append((address, size, regs[rt] & ((1 << (size * 8)) - 1)))
        else:
            raise AssertionError('Unmodeled scalar word: ' + hex(word))
        regs[0] = 0

    while steps < 10000:
        steps += 1
        word = words[pc]
        op, rs, rt, fn = word >> 26, (word >> 21) & 31, (word >> 16) & 31, word & 63
        if op in (4, 5):
            taken = (regs[rs] == regs[rt]) if op == 4 else (regs[rs] != regs[rt])
            target = pc + 1 + sext(word & 65535, 16)
            plain(words[pc + 1])
            pc = target if taken else pc + 2
        elif op == 0 and fn == 8:
            target = regs[rs]
            plain(words[pc + 1])
            assert target == incoming[31], 'Unexpected indirect jump'
            return regs, memory, reads, writes
        else:
            plain(word)
            pc += 1
    raise AssertionError('Execution did not terminate')


def logical_instruction_stream(words):
    """Independent code-order/CFG identity after removing only zero NOPs."""
    locations = [i for i, word in enumerate(words) if word != 0]
    ordinal = {location: n for n, location in enumerate(locations)}
    result = []
    for location in locations:
        word = words[location]
        if word >> 26 in (4, 5):
            target = location + 1 + sext(word & 65535, 16)
            while words[target] == 0:
                target += 1
            assert target in ordinal
            result.append((word & 0xFFFF0000, ordinal[target]))
        else:
            result.append((word, None))
    return result


def fixture(producer, exit_branch='beq $3,$5,$Lexit', backward='bne $3,$0,$Lloop', prefix=''):
    return f'''\t.text
\t.align 2
\t.globl probe
\t.ent probe
probe:
\t.frame $sp,0,$31
\t.mask 0,0
\t.fmask 0,0
{prefix}$Lloop:
\t{producer}
\t{exit_branch}
\t.set noreorder
\t.set nomacro
\t{backward}
\taddiu $4,$4,2
\t.set macro
\t.set reorder
\tmove $2,$0
$Lexit:
\tjr $31
\t.end probe
'''


def rejected_cases():
    base = fixture('lhu $3,0($4)')
    changes = {
        'wrong_condition_producer': ('lhu $3,0($4)', 'lhu $6,0($4)'),
        'zero_condition_producer': ('lhu $3,0($4)', 'lhu $0,0($4)'),
        'invalid_gpr': ('lhu $3,0($4)', 'lhu $32,0($4)'),
        'invalid_memory_base': ('lhu $3,0($4)', 'lhu $3,0($32)'),
        'expanded_memory': ('lhu $3,0($4)', 'lhu $3,65536($4)'),
        'symbolic_memory': ('lhu $3,0($4)', 'lhu $3,symbol($4)'),
        'extra_producer_operand': ('lhu $3,0($4)', 'lhu $3,0($4),$5'),
        'missing_branch_operand': ('beq $3,$5,$Lexit', 'beq $3,$Lexit'),
        'extra_branch_operand': ('beq $3,$5,$Lexit', 'beq $3,$5,$6,$Lexit'),
        'invalid_branch_register': ('beq $3,$5,$Lexit', 'beq $3,$32,$Lexit'),
        'likely_exit_beql': ('beq $3,$5,$Lexit', 'beql $3,$5,$Lexit'),
        'likely_exit_bnel': ('beq $3,$5,$Lexit', 'bnel $3,$5,$Lexit'),
        'likely_exit_beqzl': ('beq $3,$5,$Lexit', 'beqzl $3,$Lexit'),
        'likely_exit_bnezl': ('beq $3,$5,$Lexit', 'bnezl $3,$Lexit'),
        'interior_exit': ('beq $3,$5,$Lexit', 'beq $3,$5,$Lloop'),
        'missing_exit': ('beq $3,$5,$Lexit', 'beq $3,$5,$Lmissing'),
        'opaque_call': ('lhu $3,0($4)', 'jal $Lexit\n\tlhu $3,0($4)'),
        'opaque_trap': ('lhu $3,0($4)', 'syscall\n\tlhu $3,0($4)'),
        'expanded_li': ('lhu $3,0($4)', 'li $3,0x12345678'),
        'expanded_arithmetic': ('lhu $3,0($4)', 'addu $3,$4,65536'),
        'invalid_shift': ('lhu $3,0($4)', 'sll $3,$4,32'),
        'interior_join': ('lhu $3,0($4)', '$Ljoin:\n\tlhu $3,0($4)'),
        'loop_data_directive': ('lhu $3,0($4)', '.word 0\n\tlhu $3,0($4)'),
        'unknown_directive': ('.mask 0,0', '.previous'),
        'combined_label': ('$Lloop:', '$Lloop: nop'),
        'opaque_inline_asm': ('lhu $3,0($4)', '#APP\n\tlhu $3,0($4)\n#NO_APP'),
        'store_producer': ('lhu $3,0($4)', 'sh $3,0($4)'),
        'nop_producer': ('lhu $3,0($4)', 'nop'),
        'already_explicit_exit': ('beq $3,$5,$Lexit', '.set noreorder\n\tbeq $3,$5,$Lexit'),
        'reorder_nomacro_exit': ('beq $3,$5,$Lexit', '.set nomacro\n\tbeq $3,$5,$Lexit'),
        'missing_backedge_delay': ('addiu $4,$4,2', ''),
        'branch_in_backedge_delay': ('addiu $4,$4,2', 'beq $3,$5,$Lexit'),
        'expanded_backedge_delay': ('addiu $4,$4,2', 'li $4,0x12345678'),
        'unclosed_function': ('\t.end probe', ''),
        'mismatched_end': ('\t.end probe', '\t.end other'),
        'duplicate_label': ('$Lexit:', '$Lloop:\n$Lexit:'),
        'cross_function_exit': ('$Lexit:\n\tjr $31\n\t.end probe', '\t.end probe\n\t.ent other\n$Lexit:\n\tjr $31\n\t.end other'),
    }
    result = []
    for name, (old, new) in changes.items():
        assert old in base
        try:
            fix(base.replace(old, new, 1))
        except (ValueError, KeyError) as error:
            result.append({'case': name, 'status': 'REJECTED', 'reason': str(error)})
        else:
            raise AssertionError('Unsafe input admitted: ' + name)
    return result


def main():
    rng = random.Random(0x2718A0)
    source = OUT / 'source_baseline.c'
    source.write_text('// SLY3_CFLAGS: -Os -G0\n// SLY3_ASFIX: engine\nunsigned short *func_002718A0(unsigned short *text,int character) {\n    unsigned short *result; unsigned short value;\n    character &=65535; result=text;\n    for(;;) {\n        value=*result;\n        if(value==character) break;\n        if(value) ++result;\n        else {result=0;break;}\n    }\n    return result;\n}\n')
    # compile_source remains the ordinary production engine profile. The scoped
    # proposal operates only on this newly produced raw assembly in private.
    baseline_path = compile_source(source, OUT / 'source_baseline.o')
    raw = baseline_path.with_suffix('.raw.s').read_text()
    fixed, proof = fix(raw)
    assert len(proof['materialized_exit_slots']) == 1
    assert proof['engine_padded_loops'] == 1
    final, fixed_words = assemble('source_proposal', fixed)
    production_source = OUT / 'source_production.c'
    production_source.write_text(source.read_text().replace('SLY3_ASFIX: engine', 'SLY3_ASFIX: engine-exit-slots'))
    production_object = OUT / 'source_production.o'
    previous_force = os.environ.get('SLY3_FORCE_COMPILE')
    os.environ['SLY3_FORCE_COMPILE'] = '1'
    try:
        compile_source(production_source, production_object)
    finally:
        if previous_force is None:
            os.environ.pop('SLY3_FORCE_COMPILE', None)
        else:
            os.environ['SLY3_FORCE_COMPILE'] = previous_force
    assert Elf32(production_object.read_bytes()).section_data(Elf32(production_object.read_bytes()).section('.text')) == struct.pack('<' + str(len(fixed_words)) + 'I', *fixed_words)
    cache_compiler = ROOT / target_config()['compiler']
    cache_assembler = ROOT / target_config()['assembler']
    def signature():
        return source_signature(production_source, cache_compiler, cache_assembler, ['-Os','-G0'], True, (), 'engine-exit-slots')
    original_signature = signature()
    dependencies = ['tools/asfix_engine_exit_slots.py', 'tools/asfix_sly2.py', 'tools/compiler.py']
    for dependency in dependencies:
        wanted = (ROOT / dependency).resolve()
        with patch('compiler.file_hash', side_effect=lambda name: '0' * 64 if Path(name).resolve() == wanted else file_hash(name)):
            assert signature() != original_signature, dependency
    unsupported = OUT / 'source_unknown_profile.c'
    unsupported.write_text(production_source.read_text().replace('engine-exit-slots', 'engine-exit-slots-unknown'))
    try:
        compile_source(unsupported, OUT / 'unknown_profile.o')
    except ValueError as error:
        assert 'Unsupported assembler filter' in str(error)
    else:
        raise AssertionError('Unknown profile was admitted')
    _, raw_words = assemble('source_raw', raw)
    assert logical_instruction_stream(raw_words) == logical_instruction_stream(fixed_words)
    original = Elf32((ROOT / 'disc/SCUS_974.64').read_bytes())
    known = dict(functions())
    known['func_002718A0'] = (0x2718A0, 48)  # research extent, no index mutation
    strict = compare_object('func_002718A0', final, original, known,
                            ObjectLinker(final, target=original, addresses=symbol_addresses()))
    assert strict['status'] == 'EXACT_MATCH' and strict['instructions'] == 11
    assert struct.pack('<12I', *fixed_words) == original.at_vram(0x2718A0, 48)
    states = 0
    for _ in range(4096):
        values = [rng.randrange(1, 65536) for _ in range(rng.randrange(1, 35))] + [0]
        base = 0x100040
        memory = {base + i * 2 + b: (value >> (b * 8)) & 255
                  for i, value in enumerate(values) for b in range(2)}
        incoming = [rng.getrandbits(64) for _ in range(32)]
        needle = rng.choice([0, rng.choice(values), rng.randrange(65536)])
        incoming[4], incoming[5], incoming[31] = base, needle | (rng.randrange(65536) << 16), 0x400000
        before = execute(raw_words, incoming, memory)
        after = execute(fixed_words, incoming, memory)
        assert before == after
        expected = next((base + n * 2 for n, value in enumerate(values) if value == needle), 0)
        assert after[0][2] == expected
        states += 1
    fixtures = []
    # Different physical/alias branch forms and producers, including an earlier
    # independent instruction, test native scheduling rather than self-simulation.
    cases = [
        ('unsigned_half_load', 'lhu $3,0($4)', 'beq $3,$5,$Lexit', ''),
        ('signed_half_load', 'lh $3,0($4)', 'beq $3,$5,$Lexit', ''),
        ('unsigned_byte_load', 'lbu $3,0($4)', 'beq $3,$5,$Lexit', ''),
        ('word_load', 'lw $3,0($4)', 'bne $3,$5,$Lexit', ''),
        ('scalar_add', 'addiu $3,$4,-2', 'beq $3,$5,$Lexit', ''),
        ('scalar_bit', 'andi $3,$4,65535', 'bne $3,$5,$Lexit', ''),
        ('condition_alias', 'lhu $3,0($4)', 'beqz $3,$Lexit', ''),
        ('independent_before_load', 'lhu $3,0($4)', 'beq $3,$5,$Lexit', '\tori $6,$6,1\n'),
    ]
    for name, producer, branch, prefix in cases:
        text = fixture(producer, branch, prefix=prefix)
        explicit, records = materialize(text)
        proposed, detail = fix(text)
        assert len(records) == 1
        for profile in ('sn', 'gnu'):
            native_path, native = assemble(name + '_raw', text, profile)
            material_path, material = assemble(name + '_explicit', explicit, profile)
            proposed_path, padded = assemble(name + '_padded', proposed, profile)
            forward = [i for i, w in enumerate(native) if w >> 26 in (4, 5) and 0 < (w & 65535) < 32768]
            assert len(forward) == 1 and native[forward[0] + 1] == 0
            # Exact machine words for the producer remain immediately before the
            # forward branch: the assembler did not move an earlier instruction.
            assert native[forward[0] - 1] != 0
            assert logical_instruction_stream(native) == logical_instruction_stream(material) == logical_instruction_stream(padded)
            positive_states = 0
            for _ in range(128):
                memory = {0x100000 + n: rng.randrange(256) for n in range(256)}
                incoming = [rng.getrandbits(64) for _ in range(32)]
                incoming[4], incoming[5], incoming[31] = 0x100000, 0xDEADBEEF, 0x400000
                # Each synthetic exit is taken on the first iteration, except
                # BEQ forms whose equality is explicitly installed below.
                if branch.startswith(('beq ', 'beqz ')):
                    if 'beqz' in branch:
                        memory[0x100000] = memory[0x100001] = 0
                    elif producer.startswith(('lhu ', 'lh ', 'lbu ')):
                        incoming[5] = 7
                        memory[0x100000], memory[0x100001] = 7, 0
                    elif producer.startswith('addiu '):
                        incoming[5] = 0xFFFFE
                before = execute(native, incoming, memory)
                assert before == execute(material, incoming, memory) == execute(padded, incoming, memory)
                positive_states += 1
            fixtures.append({'case': name, 'assembler': profile, 'native_forward_delay_word': 0,
                             'native_object': native_path.relative_to(ROOT).as_posix(),
                             'explicit_object': material_path.relative_to(ROOT).as_posix(),
                             'proposed_object': proposed_path.relative_to(ROOT).as_posix(),
                             'all_scalar_register_memory_access_states': positive_states,
                             'non_nop_instruction_order_and_branch_successors': 'IDENTICAL',
                             'filter_evidence': detail})
    negative = rejected_cases()
    result = {'status': 'PASS', 'profile': 'engine-exit-slots', 'adapter': 'tools/asfix_engine_exit_slots.py',
              'adapter_sha256': sha((ROOT / 'tools/asfix_engine_exit_slots.py').read_bytes()),
              'default_engine_profile_unchanged': True, 'source': source.relative_to(ROOT).as_posix(),
              'source_sha256': sha(source.read_bytes()), 'strict_original_function': strict,
              'production_source': production_source.relative_to(ROOT).as_posix(),
              'production_object': production_object.relative_to(ROOT).as_posix(),
              'cache_dependency_tests': dependencies, 'unknown_profile_guard': 'REJECTED',
              'original_whole48_sha256': sha(original.at_vram(0x2718A0, 48)),
              'research_extent_only': '44 function bytes plus4 original zero alignment; indexed56 still includes8 unrelated orphan bytes. No override edited.',
              'fresh_source_native_random_states': states,
              'source_non_nop_instruction_order_and_branch_successors': 'IDENTICAL',
              'native_assembler_fixtures': fixtures, 'negative_guards': negative,
              'model_limits': 'Scalar low64 GPR and architectural branch-delay semantics. Added operations are only NOPs; loads/stores, all scalar registers and access order compare exactly. No full128 lane operations, opaque inline assembly, likely exits or ambiguous joins are admitted.',
              'causal_rule': 'A immediately preceding single scalar writer to an exit condition blocks delay filling. Its guaranteed empty delay is explicitly materialized; unchanged engine min6 policy then counts and pads the short linear nonexit path.'}
    (ROOT / 'build/reports/engine_exit_slots_validation.json').write_text(json.dumps(result, indent=2) + '\n')
    print('PASS', len(fixtures), 'native assembler fixtures;', len(negative), 'negative guards;', states + sum(x['all_scalar_register_memory_access_states'] for x in fixtures), 'scalar states')


if __name__ == '__main__':
    main()

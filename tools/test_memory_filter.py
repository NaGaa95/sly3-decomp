"""Validate exact memory routines and literal/return rewrite safety."""
from common import ROOT, save_json
from compiler import compile_source
from matchtool import compare_object
from asfix_constcopy import copy_delay_constants, fix


def main():
    verified = []
    for name in ('memcpy', 'memmove', 'memset'):
        output = compile_source(ROOT / 'src/lib/string' / (name + '.c'), ROOT / 'build/tests' / (name + '.o'))
        result = compare_object(name, output)
        assert result['status'] == 'EXACT_MATCH', result
        verified.append({'name': name, 'instructions': result['instructions'], 'status': result['status']})
    prefix = 'gcc2_compiled.:\n.ent f\nf:\n'
    plain = prefix + '\tli $2,-1\n\tli $4,-1\n.end f\n'
    assert len(copy_delay_constants(plain)[1]) == 1
    cases = {
        'label with alternate entry': plain.replace('\tli $4', 'L:\n\tli $4'),
        'aliased register clobber': plain.replace('\tli $4', '\tlw $v0,0($5)\n\tli $4'),
        'unknown operation': plain.replace('\tli $4', '\tcustom_op $2\n\tli $4'),
        'different literal': plain.replace('li $4,-1', 'li $4,-2'),
        'expanded immediate': plain.replace(',-1', ',65537'),
        'zero register initialization': plain.replace('li $2', 'li $zero'),
        'assembler temporary': plain.replace('li $2', 'li $at'),
        'annulled literal initialization': prefix + '.set noreorder\nbnel $5,$6,L\nli $2,-1\n.set reorder\nli $4,-1\nL:\n.end f\n',
        'ordinary slot register clobber': prefix + 'li $2,-1\n.set noreorder\nbne $5,$6,L\nlw $2,0($7)\n.set reorder\nli $4,-1\nL:\n.end f\n',
        'callee clobber after literal slot': prefix + '.set noreorder\njal g\nli $2,-1\n.set reorder\nli $4,-1\n.end f\n',
        'conditional link callee clobber': prefix + '.set noreorder\nbltzal $5,L\nli $2,-1\n.set reorder\nli $4,-1\nL:\n.end f\n',
    }
    for name, assembly in cases.items():
        assert not copy_delay_constants(assembly)[1], 'Unsafe literal reuse: ' + name
    # On likely fallthrough the clobber is annulled: the original literal is valid.
    likely = prefix + 'li $2,-1\n.set noreorder\nbnel $5,$6,L\nlw $2,0($7)\n.set reorder\nli $4,-1\nL:\n.end f\n'
    assert len(copy_delay_constants(likely)[1]) == 1
    return_code = prefix + 'move $v0,$8\nj $ra\n.end f\n'
    transformed, report = fix(return_code)
    assert report['filled_returns'] == 1 and 'j $ra\nmove $v0,$8' in transformed
    for assembly in (return_code.replace('move $v0', 'move $ra'), return_code.replace('j $ra', 'L:\nj $ra')):
        assert fix(assembly)[1]['filled_returns'] == 0
    save_json(ROOT / 'build/reports/memory_filter_validation.json', {
        'functions': verified, 'unsafe_literal_cases_withheld': list(cases),
        'branch_likely_fallthrough_verified': True, 'unsafe_return_moves_withheld': 2,
    })
    print('PASS: exact memcpy/memmove/memset; eleven unsafe literal cases and two unsafe return moves withheld')


if __name__ == '__main__':
    main()

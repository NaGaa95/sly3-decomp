"""Validate production math ordering against real code and unsafe input cases."""
from common import ROOT, save_json
from compiler import compile_source
from matchtool import compare_object
from asfix_fdlibm import fix


def main():
    verified = []
    for name in ("func_002A82B0", "func_002A7808", "func_002A3510"):
        source = ROOT / "src/lib/math" / (name + ".c")
        output = compile_source(source, ROOT / "build/tests" / (name + ".o"))
        result = compare_object(name, output)
        assert result["status"] == "EXACT_MATCH", result
        verified.append({"name": name, "status": result["status"], "instructions": result["instructions"]})
    prefix = 'gcc2_compiled.:\n.ent f\nf:\n'
    block = '.set noreorder\n.set nomacro\nbne $v0,$zero,L\nnop\n.set macro\n.set reorder\n'
    valid = prefix + 'mfc1 $2,$f0\n#nop\n' + block + 'L:\nj $31\n.end f\n'
    transformed, count = fix(valid)
    assert count == 1 and 'mfc1 $2,$f0\nnop\n' in transformed
    assert 'j $31\n\tnop\n' in transformed
    assert fix(valid.replace('mfc1 $2', 'mfc1 $3'))[1] == 0
    cases = {
        'inline assembly': valid.replace('f:\n', 'f:\n#APP\n'),
        'unannotated dependency': valid.replace('#nop\n', ''),
        'external conditional': prefix + 'bne $2,$3,External\nL:\n.end f\n',
        'unfilled call': prefix + 'jal g\n.end f\n',
        'literal reorder': prefix + '.set reorder\nj $31\n.end f\n',
        'nested block': valid.replace('.set nomacro', '.set noreorder\n.set nomacro'),
        'control delay': valid.replace('bne $v0,$zero,L\nnop', 'bne $v0,$zero,L\nj $31'),
        'expanded delay': valid.replace('bne $v0,$zero,L\nnop', 'bne $v0,$zero,L\nli $4,65537'),
        'opaque words': valid.replace('L:\n', 'L:\n.word 0x12345678\n'),
        'opaque incbin': valid.replace('L:\n', 'L:\n.incbin "other.bin"\n'),
        'unknown set': valid.replace('L:\n', 'L:\n.set noat\n'),
        'inline label control': valid.replace('L:\n', 'L: jal g\n'),
        'expanded control': valid.replace('bne $v0,$zero,L', 'bgt $v0,$zero,L'),
        'invalid mfc1 register': valid.replace('mfc1 $2,$f0', 'mfc1 $32,$f0'),
        'unterminated function': valid.replace('.end f\n', ''),
        'external FPU target': prefix + 'bc1f External\n.end f\n',
        'ambiguous FPU operands': prefix + 'bc1f $fcc1,L\nL:\n.end f\n',
        'external jump': prefix + 'b External\n.end f\n',
        'invalid branch register': prefix + 'bne $32,$3,L\nL:\n.end f\n',
        'extra branch operands': prefix + 'bne $2,$3,$4,L\nL:\n.end f\n',
    }
    rejected = []
    for name, source in cases.items():
        try:
            fix(source)
        except ValueError:
            rejected.append(name)
        else:
            raise AssertionError('Unsafe math ordering accepted: ' + name)
    save_json(ROOT / 'build/reports/fdlibm_filter_validation.json', {
        'functions': verified, 'physical_register_dependency_verified': True,
        'rejected_cases': rejected,
    })
    print(f'PASS: {len(verified)} exact math functions; {len(rejected)} unsafe assembler cases refused')


if __name__ == '__main__':
    main()

"""Explicit numeric-literal-only profile for the scalar SDK ABI.

This composes the existing independently checked GNU-EE2.9 numeric lowering
with the unchanged SDK64 frame/CFG/alias/delay validator. Compiler call and
argument move order is retained. Only compiler assembly is read; original
game bytes never enter this adapter. Select this per file after complete
code, data and relocation validation, not as a global assembler policy.
"""
from asfix_sly2 import classify
from asfix_sdk_softdf import lower_literal
from asfix_sdk_gp64 import fix as sdk64


def fix(assembly):
    output = []
    literals = []
    for index, line in enumerate(assembly.splitlines()):
        node = classify(line)
        if node[0] == 'insn' and node[1] in ('li.d', 'dli'):
            replacement = lower_literal(node[1], node[2])
            output.extend(replacement)
            literals.append({'source_line': index + 1, 'original': line,
                             'lowered': replacement})
        else:
            output.append(line)
    text, abi = sdk64('\n'.join(output) + '\n')
    return text, {'literal_policy': 'Existing source-only GNU-EE2.9 numeric lowering.',
                  'literals': literals, 'sdk64': abi,
                  'call_setup_policy': 'Preserve compiler move/setup order; no exchanges.'}

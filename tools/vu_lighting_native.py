"""Whole native lighting section/label/delay/metadata proof; no file writes."""
import re,struct
from common import Elf32
import hashlib
def H(data):return hashlib.sha256(data).hexdigest()
def _need(condition,message):
    if not condition:raise ValueError(message)
ENTRIES = [('light_idle', 0, 16), ('light_batch', 16, 1344), ('light_inverse_normal_matrix', 1360, 128)]
BRANCHES = [(56, 'bal', 1360), (312, 'ibne', 168), (360, 'ibeq', 1064), (424, 'ibne', 632), (600, 'ibne', 464), (616, 'b', 1032), (760, 'ibne', 1032), (1000, 'ibne', 776), (1016, 'b', 1032), (1048, 'ibne', 368), (1328, 'ibne', 1128), (1472, 'jr', None)]

def allocated(e, expected):
    _need(e.type == 1 and e.machine == 8 and (e.phnum == 0) and (e.flags == 546439204), 'Unsupported native profile/header/segments')
    a = [s for s in e.sections if s['flags'] & 2]
    _need(len(a) == 3 and {(s['name'], s['type'], s['flags']) for s in a} == {('.vutext', 1, 6), ('.vudata', 1, 3), ('.vubss', 8, 3)}, 'Unsupported allocated code/data/control section')
    t = e.section('.vutext')
    _need(t['size'] == len(expected) and e.section_data(t) == expected, 'Entire original allocated text must match')
    _need(e.section('.vudata')['size'] == e.section('.vubss')['size'] == 0, 'Whole initialized data/BSS is unowned')
    return (a, t)

def control(code):
    out = []
    ends = []
    ops = {32: 'b', 33: 'bal', 36: 'jr', 37: 'jalr', 40: 'ibeq', 41: 'ibne', 44: 'ibltz', 45: 'ibgtz', 46: 'iblez', 47: 'ibgez'}
    for i, (lo, hi) in enumerate(struct.iter_unpack('<II', code)):
        pc = i * 8
        if hi & 1073741824:
            ends.append((pc, pc + 8))
            _need(pc + 16 <= len(code), 'Incomplete original native proof')
        if hi & 2147483648:
            continue
        op = lo >> 25
        if op in ops:
            imm = lo & 2047
            imm -= 2048 if imm & 1024 else 0
            target = None if op in (36, 37) else pc + 8 + 8 * imm
            _need(pc + 8 < len(code) and (target is None or (target % 8 == 0 and 0 <= target < len(code))), 'Incomplete original native proof')
            out.append({'VU_byte_PC': pc, 'kind': ops[op], 'VU_byte_target': target, 'VU_byte_delay_pair': pc + 8, 'VI_s': lo >> 11 & 31, 'VI_t_or_link': lo >> 16 & 31, 'original_lower_word': lo})
    _need([(b['VU_byte_PC'], b['kind'], b['VU_byte_target']) for b in out] == BRANCHES and ends == [(0, 8), (1344, 1352)], 'Incomplete original native proof')
    _need(out[0]['VI_t_or_link'] == out[-1]['VI_s'] == 15, 'Incomplete original native proof')
    return (out, ends)

def native(raw, kind, expected):
    e = Elf32(raw)
    a, t = allocated(e, expected)
    syms = e.symbols()
    names = {s['name']: s for s in syms if s['name']}
    _need(len(names) == len([s for s in syms if s['name']]), 'Ambiguous named symbols')
    rels = [s for s in e.sections if s['type'] in (4, 9) and s['size']]
    resolved = []
    shadow = None
    if kind == 'program':
        _need(not rels, 'Every allocated code relocation must be resolved before acceptance')
        fs = [s for s in syms if s['type'] == 2]
        _need(sorted(((s['name'], s['value'], s['size']) for s in fs)) == sorted(ENTRIES), 'Incomplete original native proof')
        for n, b, z in ENTRIES:
            _need(names[n]['shndx'] == t['index'] and names[n]['visibility'] == 235 and (names[n]['binding'] == (0 if n == 'light_inverse_normal_matrix' else 1)), 'Incomplete original native proof')
        _need(e.section('.DVP.ovlytab')['size'] == 0 and e.section('.DVP.ovlystrtab')['size'] == 1 and (not any((s['name'].startswith('.DVP.overlay.') for s in e.sections))), 'Incomplete original native proof')
        branches, ends = control(expected)
    elif kind == 'upload':
        _need(len(rels) == 1, 'Incomplete original native proof')
        rel = rels[0]
        tab = e.section('.DVP.ovlytab')
        st = e.section('.DVP.ovlystrtab')
        sym = e.section('.symtab')
        _need(rel['name'] == '.rel.DVP.ovlytab' and rel['type'] == 9 and (rel['flags'] == 64) and (rel['size'] == 16) and (rel['entsize'] == 8) and (rel['info'] == tab['index']) and (rel['link'] == sym['index']), 'Wrong real metadata relocation section')
        _need(tab['type'] == 2147480608 and tab['flags'] == 1 and (tab['size'] == 12) and (st['type'] == 3) and (st['flags'] == 1) and (tab['alignment'] == 4), 'Incomplete original native proof')
        for off, info in struct.iter_unpack('<II', e.section_data(rel)):
            _need(off in (0, 4) and info & 255 == 2, 'Incomplete original native proof')
            symbol = syms[info >> 8]
            want = st if off == 0 else t
            addend = struct.unpack_from('<I', e.section_data(tab), off)[0]
            _need(symbol['shndx'] == want['index'] and symbol['type'] == 3 and (symbol['value'] == 0), 'Incomplete original native proof')
            resolved.append({'offset': off, 'type': 2, 'symbol': symbol['name'], 'symbol_section_index': symbol['shndx'], 'native_addend': addend, 'resolved_value': addend + (2901504 if off == 4 else 0), 'address_space': 'EE source payload' if off == 4 else 'DVP string-table offset'})
        _need({x['offset'] for x in resolved} == {0, 4}, 'Incomplete original native proof')
        no, lma, vma = struct.unpack('<III', e.section_data(tab))
        _need(no == 1 and lma == 8 and (vma == 0), 'Incomplete original native proof')
        name = e.section_data(st)[no:].split(b'\x00', 1)[0].decode()
        sh = e.section(name)
        shadows = [s for s in e.sections if s['name'].startswith('.DVP.overlay.')]
        _need(len(shadows) == 1 and sh['type'] == 2147480609 and (sh['flags'] == 5) and (sh['size'] == 1488) and (not any(e.section_data(sh))), 'Original zero shadow cannot be allocated or counted as source')
        _need(expected[:8] == struct.pack('<II', 0, 1253703680) and expected[1496:] == bytes(8), 'Incomplete original native proof')
        for n, b, z in ENTRIES:
            _need(names[n]['value'] == b and names[n]['shndx'] == sh['index'] and (names[n]['visibility'] == 235), 'Incomplete original native proof')
            m = names['_$' + n]
            _need(m['value'] == b + 8 and m['shndx'] == t['index'] and (m['visibility'] == 235), 'Incomplete original native proof')
        _need(names['light_upload_begin']['value'] == 0 and names['light_upload_end']['value'] == 1504, 'Incomplete original native proof')
        _need([x['resolved_value'] for x in resolved if x['offset'] == 4] == [2901512], 'Incomplete original native proof')
        shadow = {'name': name, 'VU_byte_begin': 0, 'EE_source_payload_address': 2901512, 'code_bytes': 1488, 'original_metadata_or_zero_shadow_bytes_source_counted': 0}
        branches, ends = control(expected[8:1496])
    else:
        _need(kind == 'runtime_REFS' and rels == [] and (expected == struct.pack('<IIII', 1073741918, 2901504, 0, 0)), 'Incomplete original native proof')
        _need(names['original_light_upload_EE_address']['value'] == 2901504 and names['original_light_upload_EE_address']['shndx'] == 65521, 'Incomplete original native proof')
        _need(names['light_runtime_REFS_begin']['value'] == 0 and names['light_runtime_REFS_end']['value'] == 16, 'Incomplete original native proof')
        _need(e.section('.DVP.ovlytab')['size'] == 0 and (not any((s['name'].startswith('.DVP.overlay.') for s in e.sections))), 'Incomplete original native proof')
        branches = []
        ends = []
    return {'kind': kind, 'whole_allocated_text_bytes': len(expected), 'whole_allocated_text_sha256': H(expected), 'allocated_sections': [dict(s, raw_hex=e.section_data(s).hex()) for s in a], 'initialized_data_bytes': 0, 'BSS_bytes': 0, 'unsupported_allocated_sections': 0, 'actual_nonallocated_metadata_relocations': resolved, 'remaining_code_relocations': [], 'zero_shadow_mapping': shadow, 'all_branch_or_return_delay_pairs': branches, 'all_E_delay_pairs': ends, 'entire_native_original_equal': True, 'runtime_control_source_credit': 0 if kind == 'runtime_REFS' else None}

def strict_native(raw, kind, expected):
    proof = native(raw, kind, expected)
    e = Elf32(raw)
    names = {x['name']: x for x in e.symbols() if x['name']}
    t = e.section('.vutext')
    schemas = {'.vutext': (1, 6, 16 if kind != 'upload' else 8, 0), '.vudata': (1, 3, 1, 0), '.vubss': (8, 3, 1, 0), '.DVP.ovlytab': (2147480608, 1, 4, 12), '.DVP.ovlystrtab': (3, 1, 1, 0), '.symtab': (2, 0, 4, 16), '.strtab': (3, 0, 1, 0), '.shstrtab': (3, 0, 1, 0)}
    if kind == 'upload':
        schemas['.rel.DVP.ovlytab'] = (9, 64, 4, 8)
    for s in e.sections[1:]:
        name = s['name']
        _need(s['addr'] == 0, 'Native object section has unsupported placed address')
        if name.startswith('.DVP.overlay.'):
            _need(kind == 'upload' and re.fullmatch('\\.DVP\\.overlay\\.\\.0x0\\.[0-9]+\\.6\\.0', name), 'Incomplete original native proof')
            _need((s['type'], s['flags'], s['alignment'], s['entsize'], s['link'], s['info']) == (2147480609, 5, 1, 0, 0, 0), 'Incomplete original native proof')
        else:
            _need(name in schemas, 'Unsupported emitted section')
            _need((s['type'], s['flags'], s['alignment'], s['entsize']) == schemas[name], 'Unsupported emitted section profile')
            if name not in ('.symtab', '.rel.DVP.ovlytab'):
                _need(s['link'] == s['info'] == 0, 'Incomplete original native proof')
    _need(len(e.sections) == (11 if kind == 'upload' else 9), 'Incomplete original native proof')
    sym = e.section('.symtab')
    _need(sym['link'] == e.section('.strtab')['index'] and sym['size'] % 16 == 0, 'Incomplete original native proof')
    for x in e.symbols():
        _need(x['shndx'] in (0, 65521) or 0 < x['shndx'] < len(e.sections), 'Native symbol section out of bounds')
    for n, value in [('object_bounds_qword', 770), ('object_matrix_qword', 771), ('vertex_spans_qword', 775), ('packet_alpha_qword', 776), ('scene_ambient_qword', 11)] if kind != 'runtime_REFS' else []:
        x = names[n]
        _need((x['value'], x['size'], x['type'], x['binding'], x['visibility'], x['shndx']) == (value, 0, 0, 0, 0, 65521), 'Incomplete original native proof')
    if kind == 'upload':
        sh = next((s for s in e.sections if s['name'].startswith('.DVP.overlay.')))
        for n, value in [('light_upload_begin', 0), ('light_upload_end', 1504)]:
            x = names[n]
            _need((x['value'], x['size'], x['type'], x['binding'], x['visibility'], x['shndx']) == (value, 0, 0, 1, 0, t['index']), 'Incomplete original native proof')
        for n, begin, size in ENTRIES:
            x = names[n]
            _need((x['value'], x['size'], x['type'], x['binding'], x['visibility'], x['shndx']) == (begin, 0, 0, 0 if n == 'light_inverse_normal_matrix' else 1, 235, sh['index']), 'Incomplete original native proof')
            x = names['_$' + n]
            _need((x['value'], x['size'], x['type'], x['binding'], x['visibility'], x['shndx']) == (begin + 8, 0, 0, 0, 235, t['index']), 'Incomplete original native proof')
        for r in proof['actual_nonallocated_metadata_relocations']:
            _need(r['native_addend'] == (1 if r['offset'] == 0 else 8), 'Incomplete original native proof')
    elif kind == 'runtime_REFS':
        for n, value in [('light_runtime_REFS_begin', 0), ('light_runtime_REFS_end', 16)]:
            x = names[n]
            _need((x['value'], x['size'], x['type'], x['binding'], x['visibility'], x['shndx']) == (value, 0, 0, 1, 0, t['index']), 'Incomplete original native proof')
        _need(e.section_data(e.section('.DVP.ovlystrtab')) == b'\x00', 'Incomplete original native proof')
    else:
        _need(e.section_data(e.section('.DVP.ovlystrtab')) == b'\x00', 'Incomplete original native proof')
    proof['strict_complete_emitted_section_schema'] = True
    proof['native_algorithm_and_upload_symbol_roles_complete'] = True
    return proof

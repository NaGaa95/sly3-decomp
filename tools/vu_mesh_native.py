"""Whole mesh VU native/code/control/overlay metadata proof; no file writes."""
import struct,hashlib
from common import Elf32
H=lambda b:hashlib.sha256(b).hexdigest()

def _closed_native(raw, kind, expected, roles):
    e = Elf32(raw)
    assert e.type == 1 and e.machine == 8 and (e.flags == 546439204) and (e.phnum == 0), 'Unsupported native ELF profile'
    allocated = [s for s in e.sections if s['flags'] & 2]
    assert len(allocated) == 3 and {(s['name'], s['type'], s['flags']) for s in allocated} == {('.vutext', 1, 6), ('.vudata', 1, 3), ('.vubss', 8, 3)}, 'Unsupported allocated native section'
    t = e.section('.vutext')
    emitted = e.section_data(t)
    assert e.section('.vudata')['size'] == e.section('.vubss')['size'] == 0, 'Unproved whole initialized data/BSS'
    diff = [i for i, (a, b) in enumerate(zip(emitted, expected)) if a != b]
    assert len(emitted) == len(expected) and (not diff), ('Whole allocated native mismatch', kind, len(emitted), len(expected), diff[:40])
    syms = e.symbols()
    names = {s['name']: s for s in syms if s['name']}
    rels = [s for s in e.sections if s['type'] in (4, 9) and s['size']]
    metadata = []
    if kind == 'program':
        assert not rels, 'Unresolved native code or metadata fields'
        assert e.section('.DVP.ovlytab')['size'] == 0 and (not any((s['name'].startswith('.DVP.overlay.') for s in e.sections)))
        funcs = [(s['name'], s['value'], s['size']) for s in syms if s['type'] == 2]
        assert sorted(funcs) == sorted(((r['name'], r['VU_byte_begin'], r['bytes']) for r in roles['functions'])), 'Incomplete actual native routine symbols'
        for r in roles['functions']:
            assert names[r['name']]['shndx'] == t['index'] and names[r['name']]['visibility'] == 235
    else:
        tab = e.section('.DVP.ovlytab')
        st = e.section('.DVP.ovlystrtab')
        syt = e.section('.symtab')
        assert len(rels) == 1 and rels[0]['name'] == '.rel.DVP.ovlytab' and (rels[0]['type'] == 9) and (rels[0]['flags'] == 64) and (rels[0]['size'] == 128) and (rels[0]['entsize'] == 8)
        assert rels[0]['info'] == tab['index'] and rels[0]['link'] == syt['index'] and (tab['size'] == 96) and (tab['flags'] == 1) and (not tab['flags'] & 2) and (tab['type'] == 2147480608)
        assert st['flags'] == 1 and st['type'] == 3
        for off, info in struct.iter_unpack('<II', e.section_data(rels[0])):
            assert info & 255 == 2 and off % 12 in (0, 4)
            s = syms[info >> 8]
            target = st if off % 12 == 0 else t
            addend = struct.unpack_from('<I', e.section_data(tab), off)[0]
            assert s['type'] == 3 and s['value'] == 0 and (s['shndx'] == target['index'])
            metadata.append({'offset': off, 'type': 2, 'symbol_section': target['name'], 'addend': addend, 'resolved_value': addend + (2903024 if target == t else 0), 'address_space': 'EE source payload' if target == t else 'DVP overlay string offset'})
        assert sorted((x['offset'] for x in metadata)) == [i * 12 + j for i in range(8) for j in (0, 4)]
        strings = e.section_data(st)
        shadows = []
        for i, (no, lma, vma) in enumerate(struct.iter_unpack('<III', e.section_data(tab))):
            name = strings[no:].split(b'\x00', 1)[0].decode()
            s = e.section(name)
            n = 2048 if i < 7 else 2008
            assert s['type'] == 2147480609 and s['flags'] == 5 and (not s['flags'] & 2) and (s['size'] == n) and (not any(e.section_data(s)))
            assert vma == i * 2048 and lma == 8 + i * (2048 + 8)
            shadows.append({'name': name, 'VU_byte_begin': vma, 'code_bytes': n, 'EE_payload_address': 2903024 + lma, 'native_addend': lma, 'original_metadata_and_zero_shadow_source_credit': 0})
        assert len([s for s in e.sections if s['name'].startswith('.DVP.overlay.')]) == 8
        assert names['mesh_upload_begin']['value'] == 0 and names['mesh_upload_end']['value'] == 16416
        for r in roles['functions']:
            s = names[r['name']]
            shadow = next((x for x in shadows if x['VU_byte_begin'] <= r['VU_byte_begin'] < x['VU_byte_begin'] + x['code_bytes']))
            assert e.sections[s['shndx']]['name'] == shadow['name'] and s['value'] == r['VU_byte_begin'] and (s['visibility'] == 235)
        for x in roles['genuine_additional_entries_not_duplicate_functions'].items():
            assert names[x[1]]['value'] == int(x[0])
    return {'entire_native_original_equal': True, 'whole_allocated_text_bytes': len(emitted), 'whole_allocated_text_sha256': H(emitted), 'entire_allocated_sections': [dict(s, raw_native_hex=e.section_data(s).hex()) for s in allocated], 'native_initialized_data_bytes': 0, 'native_BSS_bytes': 0, 'unsupported_allocated_sections': 0, 'actual_resolved_nonallocated_R32_metadata_fields': metadata, 'remaining_relocations': [], 'original_metadata_names_and_zero_shadows_source_credit': 0, 'native_all_section_records': e.sections, 'native_all_symbols': syms}

def strict_header(raw,kind):
    if not __debug__:raise ValueError('Whole native assertion gate requires an unoptimized Python verifier')
    if kind not in ['program','chain'] or len(raw)<52:raise ValueError('Truncated/foreign native ELF profile')
    h=struct.unpack_from('<16sHHIIIIIHHHHHH',raw)
    if h[0]!=bytes.fromhex('7f454c46010101000000000000000000'):raise ValueError('Wrong native ELF ident/class/endian/version/OSABI/padding')
    if (h[1],h[2],h[3],h[4],h[5],h[7],h[8],h[9],h[10],h[11])!=(1,8,1,0,0,0x20920024,52,0,0,40):raise ValueError('Unsupported entire native ELF header profile')
    if (h[12],h[13])!=((9,8) if kind=='program' else (18,17)):raise ValueError('Wrong complete native section/string index header')
    if h[6]<52 or h[6]%4 or h[6]+h[12]*40!=len(raw):raise ValueError('Invalid whole native section table bounds')
    sections=[struct.unpack_from('<10I',raw,h[6]+40*i) for i in range(h[12])]
    if any(sections[0]):raise ValueError('Nonzero native null-section header')
    for x in sections[1:]:
        if x[4]>h[6] or (x[1]!=8 and (x[4]+x[5]>h[6] or (x[5] and x[4]<52))):raise ValueError('Native section raw data escapes complete object bounds')
        if x[6]>=h[12]:raise ValueError('Invalid native section link index')
    st=sections[h[13]]
    if st[1]!=3 or st[2]!=0 or st[5]==0:raise ValueError('Wrong full native section-name table')
    names=raw[st[4]:st[4]+st[5]];seen=set()
    for x in sections:
        if x[0]>=len(names) or b'\x00' not in names[x[0]:]:raise ValueError('Invalid/truncated native section name')
        name=names[x[0]:].split(b'\x00',1)[0]
        if name in seen:raise ValueError('Duplicate complete native section name')
        seen.add(name)
    return {'ident':h[0].hex(),'type':h[1],'machine':h[2],'version':h[3],'entry':h[4],'phoff':h[5],'shoff':h[6],'flags':h[7],'ehsize':h[8],'phentsize':h[9],'phnum':h[10],'shentsize':h[11],'shnum':h[12],'shstrndx':h[13],'entire_object_bytes':len(raw),'unique_sections_and_all_raw_bounds':True}

def strict_native(raw,kind,expected,roles):
    header=strict_header(raw,kind)
    proof=_closed_native(raw,kind,expected,roles)
    e=Elf32(raw)
    schemas={'.vutext':(1,6,8,0),'.vudata':(1,3,1,0),'.vubss':(8,3,1,0),'.DVP.ovlytab':(0x7ffff420,1,4,12),'.DVP.ovlystrtab':(3,1,1,0),'.symtab':(2,0,4,16),'.strtab':(3,0,1,0),'.shstrtab':(3,0,1,0)}
    if kind=='chain':schemas['.rel.DVP.ovlytab']=(9,0x40,4,8)
    if len(e.sections)!=(18 if kind=='chain' else 9):raise ValueError('Unsupported entire mesh native section schema')
    for s in e.sections[1:]:
        if s['addr']!=0:raise ValueError('Unexpected placed native section')
        if s['name'].startswith('.DVP.overlay.'):
            if kind!='chain' or (s['type'],s['flags'],s['alignment'],s['entsize'],s['link'],s['info'])!=(0x7ffff421,5,1,0,0,0):raise ValueError('Wrong whole nonallocated overlay metadata section')
        elif s['name'] not in schemas or (s['type'],s['flags'],s['alignment'],s['entsize'])!=schemas[s['name']]:raise ValueError('Unsupported complete native section profile')
        elif s['name'] not in {'.symtab','.rel.DVP.ovlytab'} and (s['link'] or s['info']):raise ValueError('Unexpected native section link/info')
    if e.section('.symtab')['link']!=e.section('.strtab')['index']:raise ValueError('Wrong complete native symbol string table')
    names={s['name']:s for s in e.symbols() if s['name']}
    for pc,name in roles['genuine_additional_entries_not_duplicate_functions'].items():
        s=names[name]
        if s['value']!=int(pc) or s['binding']!=0 or s['visibility']!=0xeb:raise ValueError('Wrong real additional entry alias')
    proof['strict_complete_emitted_section_schema']=True
    proof['entire_native_header_and_raw_bounds']=header
    proof['verified_original_function_count']=None
    proof['source_partition_count_not_original_function_count']=37
    proof['entire_allocated_sections']=[{**s,'whole_native_sha256':H(e.section_data(s))} for s in e.sections if s['flags']&2]
    return proof

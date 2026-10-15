"""Validate a real compiled switch and reject incomplete or altered tables."""
import struct
from copy import deepcopy
from common import ROOT, Elf32, save_json
from compiler import compile_source
from matchtool import compare_object, functions
from relocate import ObjectLinker
from data_progress import object_data


def main():
    source = ROOT / 'src/reference_os/func_002701B0.c'
    output = compile_source(source, ROOT / 'build/tests/switch_table.o')
    name = 'func_002701B0'
    addresses = {name: 0x002701B0}
    linker = ObjectLinker(output, addresses)
    assert compare_object(name, output, linker=linker)['status'] == 'LINKED_MATCH'
    assert len(linker.data_matches) == 1
    raw, evidence = linker.constant_section('.rodata')
    assert len(raw) == 224 and len(evidence) == 55
    assert raw == linker.target.at_vram(linker.placements['.rodata'], len(raw))
    data, unresolved = object_data(linker, source)
    assert not unresolved and len(data) == 1 and data[0]['data_hex'] == raw.hex()
    assert data[0]['status'] == 'LINKED_DATA' and len(data[0]['relocations']) == 55
    elf = Elf32(output.read_bytes())
    rodata = elf.section('.rodata')
    rel = next(s for s in elf.sections if s['type'] == 9 and s['info'] == rodata['index'])
    first_place, first_info = struct.unpack_from('<II', elf.data, rel['offset'])
    rejected = []
    folder = ROOT / 'build/tests/switch_tables'
    folder.mkdir(parents=True, exist_ok=True)
    for label in ('changed local pointer', 'outside mapped function', 'unsupported table relocation'):
        altered = bytearray(elf.data)
        if label == 'unsupported table relocation':
            struct.pack_into('<I', altered, rel['offset'] + 4, (first_info & ~255) | 9)
        else:
            place = rodata['offset'] + first_place
            value = struct.unpack_from('<I', altered, place)[0]
            struct.pack_into('<I', altered, place, value + 4 if label == 'changed local pointer' else 0x10000)
        path = folder / (label.replace(' ', '_') + '.o')
        path.write_bytes(altered)
        bad = ObjectLinker(path, addresses)
        assert '.rodata' not in bad.placements, label
        assert compare_object(name, path, linker=bad)['status'] == 'UNRESOLVED_RELOCATION', label
        rejected.append(label)
    missing = ObjectLinker(output, {})
    assert '.rodata' not in missing.placements
    rejected.append('missing local function placement')
    # Add a contradictory original operand pair to the real object record set.
    # Both references are within the independently placed function, but the
    # second pair demands a different section base. Discovery must refuse both.
    contradictory = ObjectLinker(output, addresses)
    del contradictory.placements['.rodata']
    contradictory.data_matches.clear()
    code_index = elf.section('.text')['index']
    records = contradictory.relocations[code_index]
    extra = [deepcopy(records[0]), deepcopy(records[1])]
    extra[0]['offset'], extra[1]['offset'] = 0, 4
    records.extend(extra)
    contradictory._locate_referenced_constants()
    assert '.rodata' not in contradictory.placements
    rejected.append('contradictory code address operands')
    save_json(ROOT / 'build/reports/switch_table_validation.json', {
        'function': name, 'code_bytes': 84, 'complete_table_bytes': len(raw),
        'table_relocations': len(evidence), 'source_data_uses_relocated_bytes': True,
        'rejected_cases': rejected})
    print('PASS: real 84-byte switch and complete 224-byte/55-relocation table; five unsafe cases refused')


if __name__ == '__main__':
    main()

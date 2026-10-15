"""Check real full data sections and reject code-only and partial-data matches."""
import struct
from common import ROOT, Elf32, save_json
from compiler import compile_source
from relocate import ObjectLinker, RelocationError, symbol_addresses
from matchtool import compare_object, functions
from object_bindings import source_bindings
from data_progress import object_data


def main():
    source = ROOT / 'src/P2/bis.cpp'
    text = source.read_text()
    header, rest = text.split('\n', 1)
    if '-fno-rtti' not in header:
        header += ' -fno-rtti'
    draft = ROOT / 'build/tests/bis_data.cpp'
    draft.parent.mkdir(parents=True, exist_ok=True)
    draft.write_text(header + '\n' + rest.replace('"bis.h"', '"' + (source.parent / 'bis.h').as_posix() + '"'))
    output = compile_source(draft, draft.with_suffix('.o'))
    linker = ObjectLinker(output)
    name = '_vt$18CBinaryInputStream'
    linker.addresses['__pure_virtual'] = 0x0029B4A0
    address = linker.addresses[name]
    raw, evidence = linker.data_object(name)
    original = linker.target.at_vram(address, len(raw))
    assert len(raw) == 32 and raw == original and len(evidence) == 2
    linker.addresses['Close__18CBinaryInputStream'] += 4
    changed, _ = linker.data_object(name)
    assert changed != original, 'Changed virtual function pointer accepted'
    del linker.addresses['__pure_virtual']
    try:
        linker.data_object(name)
    except RelocationError:
        pass
    else:
        raise AssertionError('Missing virtual target accepted')
    extra_source = ROOT / 'build/tests/code_with_unplaced_data.c'
    extra_source.write_text('// SLY3_CFLAGS: -Os -G0\n'
                            'int unplaced_extra[4]={0x11223344,0x55667788,0x13579BDF,0x2468ACE0};\n'
                            'void func_001C9418(void) {}\n')
    extra_object = compile_source(extra_source, extra_source.with_suffix('.o'))
    extra_linker = ObjectLinker(extra_object)
    assert compare_object('func_001C9418', extra_object, linker=extra_linker)['status'] == 'EXACT_MATCH'
    extra_matches, extra_unresolved = object_data(extra_linker, extra_source)
    assert not extra_matches and extra_unresolved, 'Code-only match concealed unplaced emitted data'
    assert any(item.get('scope') == 'entire-emitted-initialized-section' for item in extra_unresolved)

    # Both named notification arrays remain correct while the same section's
    # unnamed switch tail is corrupted. Per-object prefixes must not admit it.
    callback_source = ROOT / 'src/P2/scene_mode_callbacks.cpp'
    callback_object = compile_source(callback_source, ROOT / 'build/tests/scene_mode_callbacks.o')
    known, addresses = source_bindings(callback_source, callback_object, functions(), symbol_addresses())
    callback_linker = ObjectLinker(callback_object, addresses=addresses)
    callback_matches, callback_unresolved = object_data(callback_linker, callback_source)
    assert not callback_unresolved and any(item['name'] == '.rodata' and item['size'] == 80 for item in callback_matches)
    bad_bytes = bytearray(callback_object.read_bytes())
    callback_elf = Elf32(bad_bytes)
    table = callback_elf.section('.rodata')
    tail_offset = table['offset'] + table['size'] - 4
    struct.pack_into('<I', bad_bytes, tail_offset, struct.unpack_from('<I', bad_bytes, tail_offset)[0] ^ 4)
    bad_object = ROOT / 'build/tests/scene_mode_partial_data.o'
    bad_object.write_bytes(bad_bytes)
    bad_linker = ObjectLinker(bad_object, addresses=addresses, placements={'.rodata': 0x00323840})
    assert compare_object('func_001CAF70', bad_object, known=known, linker=bad_linker)['status'] == 'EXACT_MATCH'
    bad_matches, bad_unresolved = object_data(bad_linker, callback_source)
    assert not bad_matches and any(item['name'] == '.rodata' for item in bad_unresolved), 'Correct named arrays concealed a changed whole-section tail'
    save_json(ROOT / 'build/reports/data_validation.json', {
        'table': name, 'address': f'0x{address:08X}', 'size': len(raw),
        'status': 'LINKED_DATA', 'relocations': evidence,
        'changed_virtual_target_rejected': True, 'missing_virtual_target_rejected': True,
        'exact_code_with_unplaced_initialized_data_rejected': True,
        'complete_80_byte_notification_and_switch_section_verified': True,
        'correct_named_arrays_with_corrupted_section_tail_rejected': True,
    })
    print('PASS: complete stream/scene data; changed/missing targets, unplaced data and corrupted unnamed tail rejected')


if __name__ == '__main__':
    main()

"""Native positive and fail-closed section/address/input guards for IOP proposal."""
import copy
import json
import struct
from pathlib import Path
from unittest.mock import patch

from iop_build import ROOT, allocated_read, current_report, expected_object_text, inspect_object, run, validate_manifest, validate_ownership
from common import Elf32

def main():
    manifest_path = ROOT / 'config/iop_partial.json'
    manifest = json.loads(manifest_path.read_text())
    report = run(manifest_path, ROOT / 'build/iop/tests/module_00')
    original = Elf32((ROOT / manifest['module']).read_bytes())
    functions, groups = validate_manifest(manifest)
    core = groups[ROOT / 'iop/src/sio2man/sio2_ctrl.c']
    section, target = allocated_read(original, 0, 40, executable=True)
    assert section['name'] == '.text' and target == original.section_data(original.section('.text'))[:40]
    object_path = ROOT / report['native_groups'][0]['native_profiles'][1]['object']
    native = Elf32(object_path.read_bytes())
    payload, allocated = inspect_object(native, core, target)
    assert payload == target and len(allocated) == 1
    negatives = []

    def rejected(name, callback):
        try:
            callback()
        except ValueError as error:
            negatives.append({'case': name, 'status': 'REJECTED', 'reason': str(error)})
        else:
            raise AssertionError('Guard accepted ' + name)

    def changed_manifest(change):
        candidate = copy.deepcopy(manifest)
        change(candidate)
        return lambda: validate_manifest(candidate)

    rejected('unknown_profile', changed_manifest(lambda item: item.update(profiles=['unknown'])))
    rejected('custom_989snd_contract_not_admitted', changed_manifest(lambda item: item.update(module='disc/irx/module_07.irx')))
    rejected('custom_spiop_contract_not_admitted', changed_manifest(lambda item: item.update(module='disc/irx/module_08.irx')))
    rejected('unreviewed_extra_function', changed_manifest(lambda item: item['functions'].append(copy.deepcopy(item['functions'][0]))))
    rejected('changed_original_boundary', changed_manifest(lambda item: item['functions'][0].update(size=24)))
    rejected('changed_original_entry', changed_manifest(lambda item: item['functions'][0].update(module_offset=4)))
    rejected('invented_incoming_api', changed_manifest(lambda item: item['functions'][0].update(signature='void sio2_ctrl_set(u32 value, u32 other)')))
    rejected('missing_actual_input', changed_manifest(lambda item: item['functions'][0].update(input_registers=['ra: return address'])))
    rejected('invented_getter_input', changed_manifest(lambda item: item['functions'][1].update(input_registers=['a0: invented value', 'ra: return address'])))
    rejected('wrong_getter_output_api', changed_manifest(lambda item: item['functions'][1].update(signature='void sio2_ctrl_get(void)')))
    rejected('ee_source_outside_separate_group', changed_manifest(lambda item: item['functions'][0].update(source='src/lib/func_002AE460.c')))
    rejected('unreviewed_source_identity', changed_manifest(lambda item: item['functions'][0].update(source_sha256='0' * 64)))

    metadata_only = copy.deepcopy(original)
    metadata_only.sections = [item for item in metadata_only.sections if not item['flags'] & 2]
    rejected('nonallocated_iopmod_overlap_never_used_as_code', lambda: allocated_read(metadata_only, 0, 20, executable=True))
    ambiguous = copy.deepcopy(original)
    ambiguous.sections.append(copy.deepcopy(ambiguous.section('.text')))
    rejected('ambiguous_allocated_address_domain', lambda: allocated_read(ambiguous, 0, 20, executable=True))
    rejected('negative_module_relative_address', lambda: allocated_read(original, -4, 20, executable=True))
    rejected('span_crosses_executable_section', lambda: allocated_read(original, original.section('.text')['size'] - 4, 8, executable=True))
    bss = next(item for item in original.sections if item['type'] == 8 and item['size'])
    rejected('nobits_is_not_file_backed_payload', lambda: allocated_read(original, bss['addr'], 4))

    reginfo = copy.deepcopy(native)
    reginfo.section('.reginfo')['flags'] |= 2
    rejected('otherwise_matching_object_with_unknown_initialized_section', lambda: inspect_object(reginfo, core, target))
    wrong_abi = copy.deepcopy(native)
    wrong_abi.flags = 1
    rejected('unmeasured_object_abi_flags', lambda: inspect_object(wrong_abi, core, target))
    wrong_type = copy.deepcopy(native)
    wrong_type.type = 0xFF80
    rejected('object_is_not_measured_relocatable_profile', lambda: inspect_object(wrong_type, core, target))
    wrong_alignment = copy.deepcopy(native)
    wrong_alignment.section('.text')['alignment'] = 16
    rejected('unreviewed_code_section_alignment', lambda: inspect_object(wrong_alignment, core, target))
    bss_object = copy.deepcopy(native)
    bss_object.section('.bss')['size'] = 4
    rejected('unexpected_allocated_bss', lambda: inspect_object(bss_object, core, target))
    extra_code = copy.deepcopy(native)
    extra_code.section('.text')['size'] += 4
    rejected('unowned_executable_tail', lambda: inspect_object(extra_code, core, target))
    relocation = copy.deepcopy(native)
    relocation.sections.append({'name': '.rel.text', 'type': 9, 'size': 8})
    rejected('unproved_actual_relocation', lambda: inspect_object(relocation, core, target))
    extra_function = copy.deepcopy(native)
    symbols = extra_function.symbols()
    extra_function.symbols = lambda: symbols + [{**symbols[-1], 'name': 'hidden_function', 'type': 2}]
    rejected('unowned_function_definition', lambda: inspect_object(extra_function, core, target))
    bad_owner = copy.deepcopy(native)
    symbols = bad_owner.symbols()
    bad_owner.symbols = lambda: [{**item, 'shndx': bad_owner.section('.reginfo')['index']} if item['type'] == 2 else item for item in symbols]
    rejected('function_ownership_not_verified_section', lambda: inspect_object(bad_owner, core, target))
    wrong_target = bytes([target[0] ^ 1]) + target[1:]
    rejected('whole_code_byte_mismatch', lambda: inspect_object(native, core, wrong_target))
    wrong_original = copy.deepcopy(manifest)
    wrong_original['module_sha256'] = '0' * 64
    wrong_manifest = ROOT / 'build/iop/tests/negative_original_manifest.json'
    wrong_manifest.write_text(json.dumps(wrong_original, indent=2) + '\n')
    failed_output = ROOT / 'build/iop/tests/negative_original_build'
    failed_output.mkdir(parents=True, exist_ok=True)
    stale_path = failed_output / 'partial_iop_report.json'
    stale_path.write_text(json.dumps({'status': 'PASS_STALE_BUILD', 'progress': {'verified_source_functions': 1, 'verified_source_code_bytes': 20}}))
    rejected('original_identity_mismatch_cannot_reuse_stale_success', lambda: run(wrong_manifest, failed_output))
    pending = json.loads(stale_path.read_text())
    assert pending['status'] == 'UNVERIFIED_CURRENT_BUILD' and pending['progress']['verified_source_functions'] == 0
    # One object group has two offsets; isolated groups use offset0 at nonzero
    # module addresses. The verifier must not confuse these two address domains.
    fresh = current_report(manifest_path, ROOT / 'build/iop/tests/module_00/partial_iop_report.json')
    assert fresh['progress']['verified_source_functions'] == 12
    isolated = next(owned for source, owned in groups.items() if owned[0]['name'] == 'sio2_stat70_get')
    assert isolated[0]['object_offset'] == 0 and isolated[0]['module_offset'] == 0x9C
    assert expected_object_text(original, isolated) == allocated_read(original, 0x9C, 20, True)[1]
    gap = copy.deepcopy(core)
    gap[1]['object_offset'] = 24
    rejected('unowned_gap_between_grouped_functions', lambda: expected_object_text(original, gap))
    object_overlap = copy.deepcopy(core)
    object_overlap[1]['object_offset'] = 16
    rejected('grouped_object_offsets_overlap', lambda: expected_object_text(original, object_overlap))
    module_overlap = copy.deepcopy(functions)
    module_overlap[1]['module_offset'] = 16
    rejected('noncontiguous_module_ownership_overlap', lambda: validate_ownership(module_overlap))
    double = copy.deepcopy(functions)
    double.append(copy.deepcopy(double[0]))
    rejected('duplicate_source_ownership', lambda: validate_ownership(double))
    metadata = copy.deepcopy(fresh)
    metadata['manifest_sha256'] = '0' * 64
    stale_report = ROOT / 'build/iop/tests/stale_report.json'
    stale_report.write_text(json.dumps(metadata))
    rejected('fresh_helper_rejects_stale_manifest', lambda: current_report(manifest_path, stale_report))
    stale_source_manifest = copy.deepcopy(manifest)
    stale_source_manifest['functions'][0]['source_sha256'] = '0' * 64
    stale_manifest = ROOT / 'build/iop/tests/stale_source_manifest.json'
    stale_manifest.write_text(json.dumps(stale_source_manifest))
    rejected('fresh_helper_rejects_stale_source_identity', lambda: current_report(stale_manifest, ROOT / 'build/iop/tests/module_00/partial_iop_report.json'))
    stale_native = copy.deepcopy(fresh)
    stale_native['native_groups'][0]['native_profiles'][0]['object_sha256'] = '0' * 64
    stale_report.write_text(json.dumps(stale_native))
    rejected('fresh_helper_rejects_stale_native_object', lambda: current_report(manifest_path, stale_report))
    stale_native = copy.deepcopy(fresh)
    stale_native['native_groups'][0]['native_profiles'][0]['native_input_hashes'] = {}
    stale_report.write_text(json.dumps(stale_native))
    rejected('fresh_helper_rejects_changed_compiler_inputs', lambda: current_report(manifest_path, stale_report))
    stale_counts = copy.deepcopy(fresh)
    stale_counts['progress']['verified_source_code_bytes'] += 4
    stale_report.write_text(json.dumps(stale_counts))
    rejected('fresh_helper_rejects_unproved_counts', lambda: current_report(manifest_path, stale_report))
    source_path = ROOT / manifest['functions'][0]['source']
    real_read = Path.read_bytes
    def source_drift(path):
        data = real_read(path)
        return data + b'\n' if path.resolve() == source_path.resolve() else data
    with patch.object(Path, 'read_bytes', source_drift):
        rejected('fresh_helper_rejects_actual_source_byte_drift', lambda: current_report(manifest_path, ROOT / 'build/iop/tests/module_00/partial_iop_report.json'))
    stale_verifier = copy.deepcopy(fresh)
    stale_verifier['verifier_sha256'] = '0' * 64
    stale_report.write_text(json.dumps(stale_verifier))
    rejected('fresh_helper_rejects_changed_verifier', lambda: current_report(manifest_path, stale_report))
    # A rehashed object with still-correct code but extra allocated metadata
    # must fail complete section inspection, rather than trusting its digest.
    mutated_bytes = bytearray(object_path.read_bytes())
    reginfo_section = native.section('.reginfo')
    struct.pack_into('<I', mutated_bytes, native.shoff + reginfo_section['index'] * native.shentsize + 8, reginfo_section['flags'] | 2)
    mutated_object = ROOT / 'build/iop/tests/unverified_allocated_metadata.o'
    mutated_object.write_bytes(mutated_bytes)
    mutated_report = copy.deepcopy(fresh)
    profile = mutated_report['native_groups'][0]['native_profiles'][1]
    profile['object'] = mutated_object.relative_to(ROOT).as_posix()
    from iop_build import digest
    profile['object_sha256'] = digest(mutated_bytes)
    stale_report.write_text(json.dumps(mutated_report))
    rejected('fresh_helper_reinspects_rehashed_unknown_allocated_section', lambda: current_report(manifest_path, stale_report))

    getter_index = next(i for i, function in enumerate(functions) if function['name'] == 'sio2_data_in')
    getter = groups[ROOT / functions[getter_index]['source']]
    _, getter_target = allocated_read(original, 0x154, 16, executable=True)
    getter_group = next(group for group in report['native_groups'] if group['functions'] == ['sio2_data_in'])
    getter_object = ROOT / getter_group['native_profiles'][1]['object']
    getter_native = Elf32(getter_object.read_bytes())
    assert inspect_object(getter_native, getter, getter_target)[0] == getter_target

    def changed_getter(change):
        return changed_manifest(lambda item: change(item['functions'][getter_index]))

    rejected('byte_getter_wrong_public_output_type', changed_getter(lambda item: item.update(signature='u32 sio2_data_in(void)')))
    rejected('byte_getter_output_not_zero_extended', changed_getter(lambda item: item.update(output_registers=['v0: sign-extended byte result'])))
    rejected('byte_getter_wrong_mmio_address', changed_getter(lambda item: item.update(volatile_address='0xBF808260')))
    rejected('byte_getter_wrong_access_width', changed_getter(lambda item: item.update(access_width_bits=32)))
    rejected('byte_getter_write_contract_instead_of_read', changed_getter(lambda item: item.update(memory_operation='write')))
    rejected('byte_getter_invented_input', changed_getter(lambda item: item.update(input_registers=['a0: invented value', 'ra: return address'])))
    rejected('byte_getter_swallowed_next_export', changed_getter(lambda item: item.update(size=20)))
    getter_overlap = copy.deepcopy(functions)
    getter_overlap[getter_index]['module_offset'] = 0x160
    rejected('byte_getter_overlaps_preserved_word_or_next_export', lambda: validate_ownership(getter_overlap))

    def changed_getter_word(index, word):
        data = bytearray(getter_object.read_bytes())
        section = getter_native.section('.text')
        struct.pack_into('<I', data, section['offset'] + index * 4, word)
        return Elf32(bytes(data))

    getter_words = struct.unpack('<4I', getter_target)
    signed_load = changed_getter_word(1, (getter_words[1] & 0x03FFFFFF) | (0x20 << 26))
    word_load = changed_getter_word(1, (getter_words[1] & 0x03FFFFFF) | (0x23 << 26))
    wrong_page = changed_getter_word(0, getter_words[0] ^ 1)
    wrong_displacement = changed_getter_word(1, getter_words[1] ^ 1)
    rejected('byte_getter_signed_load_native_body', lambda: inspect_object(signed_load, getter, getter_target))
    rejected('byte_getter_word_load_native_body', lambda: inspect_object(word_load, getter, getter_target))
    rejected('byte_getter_wrong_page_native_body', lambda: inspect_object(wrong_page, getter, getter_target))
    rejected('byte_getter_wrong_displacement_native_body', lambda: inspect_object(wrong_displacement, getter, getter_target))
    real_read = Path.read_bytes
    getter_source = ROOT / functions[getter_index]['source']
    def getter_source_drift(path):
        data = real_read(path)
        return data + b'\n' if path.resolve() == getter_source.resolve() else data
    with patch.object(Path, 'read_bytes', getter_source_drift):
        rejected('fresh_helper_rejects_actual_byte_getter_source_drift', lambda: current_report(manifest_path, ROOT / 'build/iop/tests/module_00/partial_iop_report.json'))
    signed_object = ROOT / 'build/iop/tests/unverified_signed_byte_getter.o'
    signed_object.write_bytes(signed_load.data)
    signed_report = copy.deepcopy(fresh)
    profile = next(group for group in signed_report['native_groups'] if group['functions'] == ['sio2_data_in'])['native_profiles'][1]
    profile['object'] = signed_object.relative_to(ROOT).as_posix()
    profile['object_sha256'] = digest(signed_load.data)
    stale_report.write_text(json.dumps(signed_report))
    rejected('fresh_helper_reinspects_rehashed_signed_byte_load', lambda: current_report(manifest_path, stale_report))

    # Decode the real native leaf, checking one FIFO read and zero extension
    # for every possible byte. Arbitrary caller A0 never enters the address.
    byte_states = 0
    for native_profile in getter_group['native_profiles']:
        elf = Elf32((ROOT / native_profile['object']).read_bytes())
        machine = struct.unpack('<4I', inspect_object(elf, getter, getter_target)[0])
        for byte in range(256):
            regs = [(0xA5139027 * (i + 1)) & 0xFFFFFFFF for i in range(32)]
            regs[0] = 0
            accesses = []
            for index, word in enumerate(machine):
                op, rs, rt = word >> 26, (word >> 21) & 31, (word >> 16) & 31
                if op == 15:
                    assert rs == 0
                    regs[rt] = (word & 0xFFFF) << 16
                elif op == 0x24:
                    displacement = (word & 0x7FFF) - (word & 0x8000)
                    accesses.append(((regs[rs] + displacement) & 0xFFFFFFFF, 8))
                    regs[rt] = byte & 0xFF
                elif word == 0x03E00008:
                    assert index == 2
                else:
                    assert word == 0 and index == 3
            assert accesses == [(0xBF808264, 8)] and regs[2] == byte
            byte_states += 1
    assert byte_states == 512
    assert report['progress']['verified_source_functions'] == 12
    assert report['progress']['verified_source_code_bytes'] == 236
    assert report['original_metadata_imports_exports_relocations_and_bss'] == 'PRESERVED_ORIGINAL_NOT_REBUILT_FROM_SOURCE'
    assert report['full_file_bytes_equal'] and not report['main_ee_source_index_compiler_and_progress_changed']
    results = {'status': 'PASS_NATIVE_PARTIAL_IOP_AND_GUARDS', 'native_whole_object_profiles': 22, 'source_functions_counted': 12, 'source_code_bytes_counted': 236, 'source_metadata_or_preservation_bytes_counted': 0, 'byte_getter_positive_states': byte_states, 'nonallocated_overlap_positive': 'ALLOCATED_TEXT_SELECTED', 'negative_cases': negatives, 'report': 'build/iop/tests/module_00/partial_iop_report.json'}
    (ROOT / 'build/iop/tests/iop_build_validation.json').write_text(json.dumps(results, indent=2) + '\n')
    print(f'PASS separate IOP native proof and {len(negatives)} meaningful rejection guards; twelve functions /236 bytes only.')
    return results

if __name__ == '__main__':
    main()

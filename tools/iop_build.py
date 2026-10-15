"""Separate exact IOP source build; original unowned bytes remain preservation.

Only the independently reviewed module00 zero-frame scalar accessors belong
to this initial profile. Every allocated object section and every
defined function is checked. Historical compiler identity, the original general
O32 ABI and custom 989snd/spiop relocation contracts remain unconfirmed. This
entry point does not modify or use the main EE compiler/collectors/profiles.
"""
import argparse
import hashlib
import json
import subprocess
from pathlib import Path

from common import Elf32

ROOT = Path(__file__).resolve().parents[1]
PROFILE_FLAGS = ['-Os', '-G0', '-mips1', '-mgp32', '-mfp32', '-mlong32', '-mcpu=r3000', '-malign-functions=2']
AS_FLAGS = ['-G0', '-mips1', '-mabi=32', '-O0']
PROFILE_REVISIONS = {'legacy-scalar-leaf-114': '114', 'legacy-scalar-leaf-136': '136'}
MEASURED_OBJECT_FLAGS = 0x20921000
EXPECTED_ENTRIES = [
    ('sio2_ctrl_set', 0, 20, 4, 'void sio2_ctrl_set(u32 value)', ['a0: u32 value', 'ra: return address']),
    ('sio2_ctrl_get', 20, 20, 5, 'u32 sio2_ctrl_get(void)', ['ra: return address']),
    ('sio2_stat6c_get', 0x28, 20, 6, 'u32 sio2_stat6c_get(void)', ['ra: return address']),
    ('sio2_stat70_get', 0x9C, 20, 11, 'u32 sio2_stat70_get(void)', ['ra: return address']),
    ('sio2_stat74_get', 0xE0, 20, 14, 'u32 sio2_stat74_get(void)', ['ra: return address']),
    ('sio2_unkn78_set', 0xF4, 20, 15, 'void sio2_unkn78_set(u32 value)', ['a0: u32 value', 'ra: return address']),
    ('sio2_unkn78_get', 0x108, 20, 16, 'u32 sio2_unkn78_get(void)', ['ra: return address']),
    ('sio2_unkn7c_set', 0x11C, 20, 17, 'void sio2_unkn7c_set(u32 value)', ['a0: u32 value', 'ra: return address']),
    ('sio2_unkn7c_get', 0x130, 20, 18, 'u32 sio2_unkn7c_get(void)', ['ra: return address']),
    ('sio2_stat_set', 0x164, 20, 21, 'void sio2_stat_set(u32 value)', ['a0: u32 value', 'ra: return address']),
    ('sio2_stat_get', 0x178, 20, 22, 'u32 sio2_stat_get(void)', ['ra: return address']),
    ('sio2_data_in', 0x154, 16, 20, 'u8 sio2_data_in(void)', ['ra: return address']),
]
BYTE_GETTER_CONTRACT = {
    'output_registers': ['v0: zero-extended u8 result'],
    'volatile_address': '0xBF808264',
    'access_width_bits': 8,
    'memory_operation': 'read',
}

def digest(data):
    return hashlib.sha256(data).hexdigest()

def checked_path(relative, prefix):
    path = (ROOT / relative).resolve()
    if not path.is_relative_to(ROOT) or not path.is_relative_to((ROOT / prefix).resolve()):
        raise ValueError(f'Path is outside {prefix}: {relative}')
    return path

def allocated_read(elf, address, size, executable=False):
    """Read the IRX module address domain without nonallocated .iopmod overlap."""
    if address < 0 or size <= 0 or address + size > 0x100000000:
        raise ValueError('Invalid module-relative span')
    candidates = [section for section in elf.sections if section['flags'] & 2 and section['type'] != 8 and section['addr'] <= address and address + size <= section['addr'] + section['size']]
    if len(candidates) != 1:
        raise ValueError('Expected one allocated file-backed section for module-relative span')
    section = candidates[0]
    if executable and (section['type'] != 1 or not section['flags'] & 4):
        raise ValueError('Source function span is not allocated executable PROGBITS')
    start = address - section['addr']
    return section, elf.section_data(section)[start:start + size]

def validate_manifest(manifest):
    if manifest.get('schema') != 'sly3-iop-partial-v1':
        raise ValueError('Unknown separate IOP manifest schema')
    if manifest.get('module') != 'disc/irx/module_00.irx':
        raise ValueError('Only the independently reviewed regular sio2man cohort is admitted')
    if manifest.get('profiles') != ['legacy-scalar-leaf-114', 'legacy-scalar-leaf-136']:
        raise ValueError('Unknown or incomplete measured scalar-leaf profiles')
    functions = manifest.get('functions')
    if not isinstance(functions, list) or len(functions) != len(EXPECTED_ENTRIES):
        raise ValueError('Only the twelve reviewed scalar functions belong to this profile')
    groups = {}
    validate_ownership(functions)
    for function, expected in zip(functions, EXPECTED_ENTRIES):
        identity = (function.get('name'), function.get('module_offset'), function.get('size'), function.get('export_ordinal'), function.get('signature'), function.get('input_registers'))
        if identity != expected:
            raise ValueError('Unknown original entry, boundary, export or incoming/output API')
        if function['name'] == 'sio2_data_in' and any(function.get(key) != value for key, value in BYTE_GETTER_CONTRACT.items()):
            raise ValueError('Unknown reviewed byte FIFO address, read width or zero-extended output')
        source_name = 'sio2_ctrl.c' if function['name'] in ('sio2_ctrl_set', 'sio2_ctrl_get') else function['name'] + '.c'
        if function.get('source') != 'iop/src/sio2man/' + source_name:
            raise ValueError('Unknown reviewed source group')
        expected_offset = 20 if function['name'] == 'sio2_ctrl_get' else 0
        if function.get('object_offset') != expected_offset:
            raise ValueError('Module offsets and object offsets must retain reviewed ownership')
        source = checked_path(function['source'], 'iop/src')
        if source.suffix != '.c' or not source.is_file() or digest(source.read_bytes()) != function['source_sha256']:
            raise ValueError('Source identity is not the reviewed ordinary C translation unit')
        groups.setdefault(source, []).append(function)
    return functions, groups

def validate_ownership(functions):
    names = [function.get('name') for function in functions]
    if len(names) != len(set(names)):
        raise ValueError('A source function has duplicate ownership')
    end = 0
    for function in sorted(functions, key=lambda item: item['module_offset']):
        start, size = function['module_offset'], function['size']
        if start < end or start < 0 or size <= 0 or start % 4 or size % 4:
            raise ValueError('Source spans overlap or have invalid module ownership')
        end = start + size

def expected_object_text(original, functions):
    """Every object byte is owned, while module placements may be noncontiguous."""
    expected = bytearray()
    for function in sorted(functions, key=lambda item: item['object_offset']):
        if function['object_offset'] != len(expected):
            raise ValueError('Object code has an unowned gap, overlap or duplicate placement')
        _, body = allocated_read(original, function['module_offset'], function['size'], executable=True)
        if digest(body) != function['original_code_sha256']:
            raise ValueError('Original whole function identity differs')
        expected.extend(body)
    return bytes(expected)

def inspect_object(elf, functions, target):
    if elf.type != 1 or elf.flags != MEASURED_OBJECT_FLAGS:
        raise ValueError('Object does not belong to the measured legacy scalar-leaf profile')
    symbols = [symbol for symbol in elf.symbols() if symbol['type'] == 2]
    actual = [(symbol['name'], symbol['value'], symbol['size']) for symbol in symbols]
    expected = [(function['name'], function['object_offset'], function['size']) for function in functions]
    if actual != expected:
        raise ValueError('Every emitted function must be explicitly owned and complete')
    if any(section['type'] in (4, 9) and section['size'] for section in elf.sections):
        raise ValueError('This leaf cohort has no source relocations; none may be ignored')
    allocated = [section for section in elf.sections if section['flags'] & 2 and section['size']]
    if len(allocated) != 1 or allocated[0]['name'] != '.text' or allocated[0]['type'] != 1 or allocated[0]['flags'] != 6:
        raise ValueError('Unexpected allocated payload: every initialized section needs proof')
    section = allocated[0]
    if section['addr'] != 0 or section['alignment'] != 4:
        raise ValueError('Unknown executable section address/alignment contract')
    payload = elf.section_data(section)
    if section['size'] != len(target) or payload != target:
        raise ValueError('Entire emitted code section differs from the original owned span')
    if any(elf.sections[symbol['shndx']]['index'] != section['index'] for symbol in symbols):
        raise ValueError('Function and verified code-section ownership disagree')
    return payload, [{'section': section['name'], 'type': section['type'], 'flags': section['flags'], 'size': section['size'], 'sha256': digest(payload), 'status': 'EXACT_ENTIRE_SECTION'}]

def native_inputs(revision):
    directory = ROOT / f'tools/third_party/ee-gcc2.95.3-{revision}'
    library = directory / 'lib/gcc-lib/ee/2.95.3'
    paths = [directory / 'bin/ee-gcc.exe', library / 'cc1.exe', library / 'cpp.exe', library / 'specs', ROOT / 'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe']
    return {path.relative_to(ROOT).as_posix(): digest(path.read_bytes()) for path in paths}


def run(manifest_path, output):
    if not output.resolve().is_relative_to(ROOT) or not output.resolve().is_relative_to((ROOT / 'build/iop').resolve()):
        raise ValueError('Separate IOP outputs must stay below build/iop')
    output.mkdir(parents=True, exist_ok=True)
    report_path = output / 'partial_iop_report.json'
    report_path.write_text(json.dumps({'status': 'UNVERIFIED_CURRENT_BUILD', 'progress': {'verified_source_functions': 0, 'verified_source_code_bytes': 0}, 'previous_success_must_not_count': True}, indent=2) + '\n')
    manifest_bytes = manifest_path.read_bytes()
    manifest = json.loads(manifest_bytes)
    functions, groups = validate_manifest(manifest)
    original_path = checked_path(manifest['module'], 'disc/irx')
    original_data = original_path.read_bytes()
    if digest(original_data) != manifest['module_sha256']:
        raise ValueError('Original module identity differs')
    original = Elf32(original_data)
    if original.type != 0xFF80 or original.flags != 1:
        raise ValueError('Unexpected original IRX ABI/header cohort')
    native_groups = []
    rebuilt = bytearray(original_data)
    assembler = ROOT / 'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe'
    for source, owned in groups.items():
        target = expected_object_text(original, owned)
        native = []
        assembled_code = None
        for profile in manifest['profiles']:
            revision = PROFILE_REVISIONS[profile]
            directory = ROOT / f'tools/third_party/ee-gcc2.95.3-{revision}'
            compiler = directory / 'bin/ee-gcc.exe'
            library = directory / 'lib/gcc-lib/ee/2.95.3'
            raw = output / f'{source.stem}_{revision}.raw.s'
            obj = output / f'{source.stem}_{revision}.o'
            commands = [[str(compiler), '-S', '-x', 'c', *PROFILE_FLAGS, '-B' + library.as_posix() + '/', source.as_posix(), '-o', raw.as_posix()], [str(assembler), *AS_FLAGS, '-o', obj.as_posix(), raw.as_posix()]]
            for command in commands:
                result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, timeout=60)
                if result.returncode:
                    raise RuntimeError(json.dumps({'command': command, 'exit': result.returncode, 'stdout': result.stdout, 'stderr': result.stderr}))
            object_data = obj.read_bytes()
            code, sections = inspect_object(Elf32(object_data), owned, target)
            if assembled_code is not None and assembled_code != code:
                raise ValueError('Independent native profiles disagree')
            assembled_code = code
            native.append({'profile': profile, 'compiler_flags': PROFILE_FLAGS, 'assembler_flags': AS_FLAGS, 'native_input_hashes': native_inputs(revision), 'assembly': raw.relative_to(ROOT).as_posix(), 'assembly_sha256': digest(raw.read_bytes()), 'assembly_unchanged': True, 'object': obj.relative_to(ROOT).as_posix(), 'object_sha256': digest(object_data), 'verified_allocated_sections': sections, 'every_initialized_section_verified': True, 'object_relocation_count': 0, 'object_elf_flags': f'0x{Elf32(object_data).flags:08X}'})
        native_groups.append({'source': source.relative_to(ROOT).as_posix(), 'source_sha256': digest(source.read_bytes()), 'functions': [function['name'] for function in owned], 'native_profiles': native})
        for function in owned:
            section, _ = allocated_read(original, function['module_offset'], function['size'], executable=True)
            file_start = section['offset'] + function['module_offset'] - section['addr']
            object_start = function['object_offset']
            rebuilt[file_start:file_start + function['size']] = assembled_code[object_start:object_start + function['size']]
    rebuilt = bytes(rebuilt)
    if rebuilt != original_data:
        raise ValueError('Full partial module bytes differ from original')
    partial_path = output / 'module_00.partial.irx'
    partial_path.write_bytes(rebuilt)
    total_size = sum(function['size'] for function in functions)
    preserved_sections = []
    for section in original.sections:
        if section['size']:
            ranges = [{'module_offset': function['module_offset'], 'size': function['size']} for function in functions if section['flags'] & 2 and section['type'] != 8 and section['addr'] <= function['module_offset'] and function['module_offset'] + function['size'] <= section['addr'] + section['size']]
            owned_size = sum(item['size'] for item in ranges)
            preserved_sections.append({'section': section['name'], 'type': section['type'], 'flags': section['flags'], 'size': section['size'], 'source_verified_bytes': owned_size, 'source_ranges': ranges, 'original_preserved_bytes': section['size'] - owned_size, 'file_backed': section['type'] != 8, 'allocated': bool(section['flags'] & 2), 'classification': 'SOURCE_RANGES_PLUS_PRESERVATION' if ranges else 'ORIGINAL_PRESERVATION'})
    records = [{**function, 'status': 'EXACT', 'source_code_bytes': function['size'], 'initialized_data_bytes': 0, 'actual_relocations': 0} for function in functions]
    report = {'status': 'PASS_SEPARATE_PARTIAL_IOP_SOURCE_BUILD', 'manifest': manifest_path.resolve().relative_to(ROOT).as_posix(), 'manifest_sha256': digest(manifest_bytes), 'verifier_sha256': digest(Path(__file__).read_bytes()), 'module': manifest['module'], 'module_sha256': digest(original_data), 'partial_module': partial_path.relative_to(ROOT).as_posix(), 'partial_module_sha256': digest(rebuilt), 'full_file_bytes_equal': True, 'functions': records, 'native_groups': native_groups, 'progress': {'verified_source_functions': len(records), 'verified_source_code_bytes': total_size, 'verified_source_initialized_data_bytes': 0, 'preserved_original_file_bytes_excluded_from_source': len(original_data) - total_size, 'original_file_size': len(original_data), 'original_text_bytes_including_tables_and_stubs': original.section('.text')['size']}, 'original_section_ownership': preserved_sections, 'original_metadata_imports_exports_relocations_and_bss': 'PRESERVED_ORIGINAL_NOT_REBUILT_FROM_SOURCE', 'native_object_header_note': 'Legacy EE assembler tags objects 0x20921000 despite MIPS1 options; only complete exact MIPS1-compatible scalar code is admitted. Original IRX header is preservation, not generated.', 'historical_iop_compiler_identity': 'UNCONFIRMED', 'general_original_o32_abi': 'NOT_CONFIRMED_BY_ZERO_FRAME_SCALAR_LEAVES', 'custom_989snd_spiop_relocations': 'UNRESOLVED_AND_NOT_ADMITTED', 'main_ee_source_index_compiler_and_progress_changed': False}
    report_path.write_text(json.dumps(report, indent=2) + '\n')
    print(f'PASS separate IOP build: {len(records)} ordinary C functions / {total_size} exact code bytes; all allocated object sections verified; original metadata/remaining bytes are preservation; full module hash equal.')
    return report


def current_report(manifest_path=None, report_path=None):
    """Read-only fresh counts; never compile, repair, mutate or reuse stale success."""
    manifest_path = Path(manifest_path) if manifest_path is not None else ROOT / 'config/iop_partial.json'
    report_path = Path(report_path) if report_path is not None else ROOT / 'build/iop/module_00/partial_iop_report.json'
    manifest_bytes = manifest_path.read_bytes()
    manifest = json.loads(manifest_bytes)
    functions, groups = validate_manifest(manifest)
    report = json.loads(report_path.read_text())
    if report.get('status') != 'PASS_SEPARATE_PARTIAL_IOP_SOURCE_BUILD' or report.get('manifest_sha256') != digest(manifest_bytes) or report.get('verifier_sha256') != digest(Path(__file__).read_bytes()):
        raise ValueError('IOP report is unverified or stale for the current manifest/verifier')
    original_data = checked_path(manifest['module'], 'disc/irx').read_bytes()
    if digest(original_data) != manifest['module_sha256'] or report.get('module_sha256') != manifest['module_sha256']:
        raise ValueError('IOP report is stale for the original module')
    original = Elf32(original_data)
    actual_functions = [{key: record.get(key) for key in function} for record, function in zip(report.get('functions', []), functions)]
    if len(report.get('functions', [])) != len(functions) or actual_functions != functions or any(record.get('status') != 'EXACT' for record in report['functions']):
        raise ValueError('IOP report function ownership differs from the current manifest')
    actual_groups = report.get('native_groups', [])
    if len(actual_groups) != len(groups):
        raise ValueError('IOP report object-group ownership differs')
    for group, (source, owned) in zip(actual_groups, groups.items()):
        if group.get('source') != source.relative_to(ROOT).as_posix() or group.get('source_sha256') != digest(source.read_bytes()) or group.get('functions') != [function['name'] for function in owned]:
            raise ValueError('IOP native object group is stale for source or ownership')
        target = expected_object_text(original, owned)
        profiles = group.get('native_profiles', [])
        if [profile.get('profile') for profile in profiles] != manifest['profiles']:
            raise ValueError('IOP native profiles are incomplete or unknown')
        for profile in profiles:
            revision = PROFILE_REVISIONS[profile['profile']]
            if profile.get('compiler_flags') != PROFILE_FLAGS or profile.get('assembler_flags') != AS_FLAGS or profile.get('native_input_hashes') != native_inputs(revision):
                raise ValueError('IOP compiler/assembler inputs changed after the verified build')
            obj = checked_path(profile['object'], 'build/iop')
            raw = checked_path(profile['assembly'], 'build/iop')
            object_data = obj.read_bytes()
            if digest(object_data) != profile.get('object_sha256') or digest(raw.read_bytes()) != profile.get('assembly_sha256'):
                raise ValueError('IOP native object or assembly changed after verification')
            _, sections = inspect_object(Elf32(object_data), owned, target)
            if sections != profile.get('verified_allocated_sections'):
                raise ValueError('IOP complete section proof differs from the recorded evidence')
    partial = checked_path(report['partial_module'], 'build/iop').read_bytes()
    if partial != original_data or digest(partial) != report.get('partial_module_sha256'):
        raise ValueError('IOP partial module differs or is stale')
    counts = {'verified_source_functions': len(functions), 'verified_source_code_bytes': sum(function['size'] for function in functions), 'verified_source_initialized_data_bytes': 0, 'preserved_original_file_bytes_excluded_from_source': len(original_data) - sum(function['size'] for function in functions), 'original_file_size': len(original_data), 'original_text_bytes_including_tables_and_stubs': original.section('.text')['size']}
    if report.get('progress') != counts:
        raise ValueError('IOP source counts differ from current complete proofs')
    return {**report, 'freshness': 'CURRENT_MANIFEST_SOURCE_MODULE_OBJECTS_AND_COMPLETE_SECTIONS_VERIFIED'}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--manifest', type=Path, default=ROOT / 'config/iop_partial.json')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/iop/module_00')
    arguments = parser.parse_args()
    run(arguments.manifest, arguments.output)

if __name__ == '__main__':
    main()

"""Assemble and verify the nine Sly 3 USA VU programs."""
import argparse
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import uuid
from pathlib import Path

sys.dont_write_bytecode = True
from common import Elf32

ORIGINAL_SHA256 = 'ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
FAMILIES = {'188059931': 8, '11753275': 7, '376118779': 1, '752237851': 3,
            '376118843': None, '1504484043': None, '188058715': None,
            '376117691': None, '188058427': None}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def receipt(path):
    data = path.read_bytes()
    return {'path': str(path), 'bytes': len(data), 'sha256': digest(data)}


def save(path, value):
    path.write_text(json.dumps(value, indent=2) + '\n', encoding='utf-8')


def source_path(root, relative):
    path = (root / relative).resolve()
    require(Path(relative).as_posix() == relative and not Path(relative).is_absolute()
            and path.is_relative_to(root / 'src/vu'), 'Source escapes src/vu')
    return path


def cstring(data, offset):
    require(0 <= offset < len(data) and b'\0' in data[offset:], 'Invalid metadata string')
    return data[offset:data.index(b'\0', offset)].decode('ascii')


def original_inputs(config, original):
    raw = original.read_bytes()
    require(digest(raw) == ORIGINAL_SHA256 == config['original']['sha256']
            and len(raw) == config['original']['bytes'], 'Wrong Sly 3 USA original ELF')
    e = Elf32(raw)
    table = e.section('.DVP.ovlytab')
    require((table['type'], table['flags'], table['size'], table['entsize'])
            == (0x7ffff420, 1, 348, 12), 'Wrong original 29-chunk overlay table')
    strings = e.section_data(e.sections[table['link']])
    actual = set()
    for name, address, vu in struct.iter_unpack('<III', e.section_data(table)):
        shadow = e.section(cstring(strings, name))
        require(shadow['type'] == 0x7ffff421 and shadow['flags'] == 5
                and not any(e.section_data(shadow)), 'Wrong original nonallocated shadow')
        actual.add((vu, address, shadow['size']))
    require(len(actual) == 29, 'Duplicate original upload chunks')
    programs = config['programs']
    require(config['schema'] == 1 and config['assembler']['version'] == '2.45.1'
            and config['program_flags'] == ['--defsym', 'VU_NATIVE_STANDALONE=1']
            and config['upload_flags'] == [], 'Unsupported source/compiler profile')
    require(len(programs) == 9 and {p['family'] for p in programs} == set(FAMILIES),
            'Missing or duplicate VU source family')
    expected, seen, spans = {}, set(), []
    for p in programs:
        require(p['original_function_count'] == FAMILIES[p['family']]
                and (p['original_function_count'] is None
                     or type(p['original_function_count']) is int), 'False original function count')
        chunks = [tuple(x) for x in p['chunks']]
        cursor = 0
        for vu, address, size in chunks:
            require((vu, address, size) in actual and (vu, address, size) not in seen
                    and vu == cursor and size > 0 and size % 8 == 0, 'Wrong original chunk ownership')
            seen.add((vu, address, size))
            cursor += size
        begin, size = p['upload_address'], p['upload_bytes']
        require(not any(begin < b and a < begin + size for a, b in spans), 'Overlapping whole uploads')
        spans.append((begin, begin + size))
        require(all(begin <= address and address + n <= begin + size for _, address, n in chunks),
                'Original instruction chunk outside whole upload')
        code = b''.join(e.at_vram(address, n) for _, address, n in chunks)
        upload = e.at_vram(begin, size)
        require(len(code) == p['code_bytes'] and digest(code) == p['code_sha256']
                and digest(upload) == p['upload_sha256'], 'Wrong whole original code/upload mapping')
        require(p['code_bytes'] + p['DMA_bytes'] + p['VIF_bytes'] == size,
                'Code and protocol byte accounting differs')
        expected[p['family']] = {'program': code, 'upload': upload}
    require(seen == actual and sum(p['code_bytes'] for p in programs) == 50032
            and sum(p['DMA_bytes'] for p in programs) == 32
            and sum(p['VIF_bytes'] for p in programs) == 320
            and sum(p['upload_bytes'] for p in programs) == 50384, 'Incomplete nine-program inventory')
    return expected


def native_object(raw, kind, program, expected, partitions=None):
    require(len(raw) >= 52, 'Truncated native object')
    h = struct.unpack_from('<16sHHIIIIIHHHHHH', raw)
    count = 9 if kind == 'program' else 10 + len(program['chunks'])
    require(h[0] == bytes.fromhex('7f454c46010101000000000000000000')
            and (h[1], h[2], h[3], h[4], h[5], h[7], h[8], h[9], h[10], h[11])
            == (1, 8, 1, 0, 0, 0x20920024, 52, 0, 0, 40)
            and (h[12], h[13]) == (count, count - 1), 'Wrong complete native ELF profile')
    require(h[6] >= 52 and h[6] % 4 == 0 and h[6] + count * 40 == len(raw),
            'Invalid entire native section table')
    headers = [struct.unpack_from('<10I', raw, h[6] + i * 40) for i in range(count)]
    require(not any(headers[0]), 'Nonzero null section')
    ranges = []
    for s in headers[1:]:
        require(s[4] <= h[6] and (s[1] == 8 or s[4] + s[5] <= h[6])
                and s[6] < count, 'Native section escapes complete object')
        if s[1] != 8 and s[5]:
            require(s[4] >= 52 and not any(s[4] < b and a < s[4] + s[5] for a, b in ranges),
                    'Overlapping native sections')
            ranges.append((s[4], s[4] + s[5]))
    strings = headers[h[13]]
    require(strings[1:3] == (3, 0), 'Wrong native section string table')
    names = [cstring(raw[strings[4]:strings[4] + strings[5]], s[0]) for s in headers]
    require(len(set(names)) == len(names), 'Duplicate native section name')
    e = Elf32(raw)
    schemas = {'.vutext': (1, 6, program['text_alignment'][kind], 0),
               '.vudata': (1, 3, 1, 0), '.vubss': (8, 3, 1, 0),
               '.DVP.ovlytab': (0x7ffff420, 1, 4, 12), '.DVP.ovlystrtab': (3, 1, 1, 0),
               '.symtab': (2, 0, 4, 16), '.strtab': (3, 0, 1, 0), '.shstrtab': (3, 0, 1, 0)}
    if kind == 'upload':
        schemas['.rel.DVP.ovlytab'] = (9, 0x40, 4, 8)
    shadows = [s for s in e.sections if s['name'].startswith('.DVP.overlay.')]
    require({s['name'] for s in e.sections[1:]} == set(schemas) | {s['name'] for s in shadows}
            and len(shadows) == (0 if kind == 'program' else len(program['chunks'])),
            'Unsupported complete native section inventory')
    for s in e.sections[1:]:
        shape = (s['type'], s['flags'], s['alignment'], s['entsize'])
        require(s['addr'] == 0 and shape == ((0x7ffff421, 5, 1, 0) if s in shadows else schemas[s['name']]),
                'Wrong whole native section profile')
        if s['name'] not in ['.symtab', '.rel.DVP.ovlytab']:
            require(s['link'] == s['info'] == 0, 'Unexpected native section link/info')
    allocated = [s for s in e.sections if s['flags'] & 2]
    require({s['name'] for s in allocated} == {'.vutext', '.vudata', '.vubss'}
            and e.section('.vudata')['size'] == e.section('.vubss')['size'] == 0,
            'Unproved allocated code/data/BSS')
    emitted = e.section_data(e.section('.vutext'))
    require(emitted == expected, 'Whole native code or upload differs from original')
    st = e.section('.symtab')
    require(st['link'] == e.section('.strtab')['index'] and st['size'] % 16 == 0
            and st['info'] <= st['size'] // 16, 'Invalid complete native symbol table')
    symbols = e.symbols()
    require(not any(s['name'] and s['shndx'] == 0 for s in symbols), 'Undefined native symbol')
    require(st['info'] == (6 if kind == 'program' else 6 + len(program['chunks']))
            and all(s['binding'] in [0, 1] for s in symbols), 'Wrong native DVP symbol profile')
    by_name = {s['name']: s for s in symbols if s['name']}
    relocations = [s for s in e.sections if s['type'] in [4, 9]]
    fields, storage = [], []
    if kind == 'program':
        require(not relocations and e.section('.DVP.ovlytab')['size'] == 0
                and e.section_data(e.section('.DVP.ovlystrtab')) == b'\0', 'Unresolved program metadata')
        partitions = sorted((s['value'], s['size'], s['name']) for s in symbols if s['type'] == 2)
        require(len(partitions) == program['source_partition_count'], 'Incomplete source partition symbols')
        cursor = 0
        for address, size, name in partitions:
            s = by_name[name]
            require(address == cursor and size > 0 and size % 8 == 0
                    and s['shndx'] == e.section('.vutext')['index'] and s['visibility'] == 235,
                    'Wrong whole source partition extent')
            cursor += size
        require(cursor == len(expected), 'Partial source partition coverage')
    else:
        tab, strings = e.section('.DVP.ovlytab'), e.section('.DVP.ovlystrtab')
        require(len(relocations) == 1 and relocations[0]['name'] == '.rel.DVP.ovlytab',
                'Allocated or unsupported native relocations')
        rel = relocations[0]
        require(rel['link'] == st['index'] and rel['info'] == tab['index']
                and rel['size'] == len(shadows) * 16 and tab['size'] == len(shadows) * 12,
                'Incomplete whole overlay relocation table')
        entries = list(struct.iter_unpack('<III', e.section_data(tab)))
        for offset, info in struct.iter_unpack('<II', e.section_data(rel)):
            require(info & 255 == 2 and offset in {12 * i + j for i in range(len(entries)) for j in [0, 4]}
                    and info >> 8 < len(symbols), 'Wrong actual R32 relocation')
            sym = symbols[info >> 8]
            target = strings if offset % 12 == 0 else e.section('.vutext')
            addend = struct.unpack_from('<I', e.section_data(tab), offset)[0]
            require(sym['type'] == 3 and sym['value'] == 0 and sym['shndx'] == target['index'],
                    'Unsupported R32 symbol or section')
            fields.append({'offset': offset, 'type': 2, 'section': target['name'], 'addend': addend,
                           'resolved': addend + (program['upload_address'] if offset % 12 else 0)})
        require(sorted(x['offset'] for x in fields) == [12 * i + j for i in range(len(entries)) for j in [0, 4]],
                'Duplicate or missing actual R32 fields')
        used = set()
        for (no, lma, vma), (vu, address, size) in zip(entries, program['chunks']):
            shadow = e.section(cstring(e.section_data(strings), no))
            data = e.section_data(shadow)
            require(shadow in shadows and shadow['name'] not in used and shadow['size'] == size
                    and vma == vu and program['upload_address'] + lma == address,
                    'Wrong complete original overlay chunk mapping')
            require(len(data) == size and len(set(data)) == 1, 'Nonuniform nonallocated sizing shadow')
            used.add(shadow['name'])
            storage.append({'name': shadow['name'], 'VU_address': vu, 'EE_address': address,
                            'bytes': size, 'fill': data[0], 'sha256': digest(data), 'source_credit': 0})
        for address, size, name in partitions:
            sym = by_name[name]
            shadow = next(x for x in storage if x['VU_address'] <= address < x['VU_address'] + x['bytes'])
            require(sym['value'] == address and sym['visibility'] == 235
                    and e.sections[sym['shndx']]['name'] == shadow['name'], 'Wrong upload source label mapping')
    proof = {'kind': kind, 'object_sha256': digest(raw), 'whole_text_bytes': len(emitted),
             'whole_text_sha256': digest(emitted), 'initialized_data_bytes': 0, 'BSS_bytes': 0,
             'allocated_relocations': 0, 'resolved_nonallocated_R32': fields,
             'nonallocated_sizing_shadows': storage, 'source_partition_count': len(partitions),
             'original_function_count': program['original_function_count']}
    return proof, emitted, partitions


def build(root, manifest, original, assembler, output):
    config = json.loads(manifest.read_text(encoding='utf-8'))
    expected = original_inputs(config, original)
    source_before = {}
    for p in config['programs']:
        for key in ['source', 'upload_source']:
            path = source_path(root, p[key])
            require(digest(path.read_bytes()) == p[key + '_sha256'], 'Changed readable source: ' + p[key])
            source_before[str(path)] = receipt(path)
    require(not output.exists() and output.is_relative_to(root / 'build'), 'Choose a new output directory below build')
    executable = Path(shutil.which(assembler) or assembler).resolve()
    require(executable.is_file(), 'dvp-as not found; supply --assembler or install the configured default')
    output.mkdir(parents=True)
    report = {'status': 'STARTED', 'original': receipt(original), 'manifest': receipt(manifest),
              'builder': receipt(Path(__file__).resolve()), 'ELF_reader': receipt(Path(sys.modules[Elf32.__module__].__file__).resolve()),
              'assembler': receipt(executable),
              'source_inputs': source_before, 'commands': [], 'programs': []}
    save(output / 'build_log.json', report)
    try:
        version = subprocess.run([str(executable), '--version'], capture_output=True, text=True, timeout=30)
        report['version_probe'] = {'argv': [str(executable), '--version'], 'exit_code': version.returncode,
                                   'stdout': version.stdout, 'stderr': version.stderr}
        save(output / 'build_log.json', report)
        require(version.returncode == 0 and not version.stderr and version.stdout.startswith('GNU assembler')
                and re.search(r'\b2\.45\.1\b', version.stdout.splitlines()[0]), 'GNU dvp-as 2.45.1 is required')
        for p in config['programs']:
            folder = output / p['family']
            folder.mkdir()
            temp = folder / ('temp_' + str(uuid.uuid4()))
            temp.mkdir()
            env = os.environ.copy()
            for key in ['TEMP', 'TMP', 'TMPDIR']:
                env[key] = str(temp)
            proofs, partitions = {}, None
            for kind, source_key in [('program', 'source'), ('upload', 'upload_source')]:
                source = source_path(root, p[source_key])
                obj = folder / (kind + '.o')
                flags = config['program_flags' if kind == 'program' else 'upload_flags']
                argv = [str(executable), '-I', str(source.parent), *flags, '-o', str(obj), str(source)]
                command = {'family': p['family'], 'kind': kind, 'argv': argv, 'cwd': str(source.parent),
                           'TEMP': str(temp), 'TMP': str(temp), 'TMPDIR': str(temp), 'source': receipt(source)}
                report['commands'].append(command)
                save(output / 'build_log.json', report)
                result = subprocess.run(argv, cwd=source.parent, env=env, capture_output=True, text=True, timeout=60)
                command.update(exit_code=result.returncode, stdout=result.stdout, stderr=result.stderr)
                save(output / 'build_log.json', report)
                require(result.returncode == 0 and not result.stdout and not result.stderr,
                        'Assembly failed or emitted diagnostics: ' + p['family'] + '/' + kind)
                proof, emitted, partitions = native_object(obj.read_bytes(), kind, p, expected[p['family']][kind], partitions)
                binary = folder / (kind + '.bin')
                binary.write_bytes(emitted)
                proofs[kind] = {**proof, 'object': receipt(obj), 'binary': receipt(binary)}
            report['programs'].append({'family': p['family'], 'native': proofs})
            save(output / 'build_log.json', report)
        require(len(report['commands']) == 18
                and sum(len(p['native']['upload']['resolved_nonallocated_R32']) for p in report['programs']) == 58,
                'Incomplete native source build')
        require(all(receipt(Path(p)) == value for p, value in source_before.items()), 'Sources changed during build')
        report.update(status='PASS', code_bytes=50032, protocol_bytes=352, whole_upload_bytes=50384,
                      overlay_chunks=29, resolved_nonallocated_R32=58, initialized_data_bytes=0, BSS_bytes=0,
                      known_original_function_count=19, unknown_original_function_count_programs=[k for k, v in FAMILIES.items() if v is None],
                      new_decompilation_credit=0, full_game_source_relink_complete=False)
    except BaseException as error:
        report.update(status='FAIL', error={'type': type(error).__name__, 'message': str(error)})
        save(output / 'build_log.json', report)
        raise
    save(output / 'build_log.json', report)
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--manifest', type=Path)
    parser.add_argument('--original', type=Path)
    parser.add_argument('--assembler')
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    root = args.root.resolve()
    manifest = (args.manifest or root / 'config/vu_build.json').resolve()
    config = json.loads(manifest.read_text(encoding='utf-8'))
    original = (args.original or root / config['original']['path']).resolve()
    assembler = args.assembler or str(root / config['assembler']['default'])
    output = (args.output or root / 'build/vu_sources' / str(uuid.uuid4())).resolve()
    report = build(root, manifest, original, assembler, output)
    print(f"PASS: {len(report['programs'])} VU programs, 50032 code bytes, 352 protocol bytes, 58 R32 fields")
    print(output / 'build_log.json')


if __name__ == '__main__':
    main()

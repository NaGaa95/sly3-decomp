"""Compare compiler-generated initialized data after resolving actual relocations."""
import hashlib
from common import ROOT, save_json
from relocate import RelocationError


def object_data(linker, source):
    matches, unresolved = [], []
    relative = source.relative_to(ROOT).as_posix()
    for section in linker.data_matches:
        raw, evidence = linker.constant_section(section['section'])
        if raw != linker.target.at_vram(section['address'], len(raw)):
            raise RelocationError('Complete relocated constant section bytes differ')
        matches.append({
            'name': section['section'], 'address': section['address'],
            'size': len(raw), 'data_hex': raw.hex(), 'source': relative,
            'status': 'LINKED_DATA' if evidence else 'EXACT_DATA', 'sha256': hashlib.sha256(raw).hexdigest(),
            'evidence': section.get('evidence', 'unique-complete-constant-section'),
            'relocations': evidence,
        })
    for symbol in linker.symbols:
        if symbol['type'] != 1 or not symbol['size'] or symbol['name'] not in linker.addresses:
            continue
        if not 0 < symbol['shndx'] < len(linker.elf.sections):
            continue
        section = linker.elf.sections[symbol['shndx']]
        if section['type'] != 1 or not section['flags'] & 2 or section['flags'] & 4:
            continue
        name, address = symbol['name'], linker.addresses[symbol['name']]
        try:
            raw, evidence = linker.data_object(name)
            original = linker.target.at_vram(address, len(raw))
            if raw != original:
                raise RelocationError('Complete initialized object bytes differ')
        except (RelocationError, ValueError) as error:
            unresolved.append({'name': name, 'source': relative, 'address': f'0x{address:08X}', 'reason': str(error)})
            continue
        matches.append({
            'name': name, 'address': address, 'size': len(raw), 'data_hex': raw.hex(),
            'source': relative, 'status': 'LINKED_DATA' if evidence else 'EXACT_DATA',
            'sha256': hashlib.sha256(raw).hexdigest(), 'relocations': evidence,
        })
    # A matching named object must never conceal another emitted section or
    # unverified bytes beside it. Admit complete initialized sections only.
    verified_sections = {match['name'] for match in matches
                         if match['name'] in {section['name'] for section in linker.elf.sections}}
    for section in linker.elf.sections:
        if section['type'] != 1 or not section['flags'] & 2 or section['flags'] & 4 or not section['size']:
            continue
        name = section['name']
        if name in verified_sections:
            continue
        original_placement = linker.placements.get(name)
        # Canonical named definitions can establish the section base, but all
        # definitions must agree and the complete relocated section must match.
        bases = {linker.addresses[symbol['name']] - symbol['value']
                 for symbol in linker.symbols
                 if symbol['type'] == 1 and symbol['size'] and symbol['shndx'] == section['index']
                 and symbol['name'] in linker.addresses}
        if original_placement is None and len(bases) == 1:
            base = next(iter(bases))
            if base % max(1, section['alignment']) == 0:
                linker.placements[name] = base
        try:
            raw, evidence = linker.constant_section(name)
            address = linker.placements[name]
            original_section = next((candidate for candidate in linker.target.sections
                                     if candidate['type'] == 1 and candidate['flags'] & 2 and not candidate['flags'] & 4
                                     and candidate['addr'] <= address
                                     and address + len(raw) <= candidate['addr'] + candidate['size']), None)
            if original_section is None or raw != linker.target.at_vram(address, len(raw)):
                raise RelocationError('Complete emitted initialized section bytes differ')
        except (RelocationError, ValueError) as error:
            if original_placement is None:
                linker.placements.pop(name, None)
            unresolved.append({'name': name, 'source': relative,
                               'size': section['size'], 'reason': str(error),
                               'scope': 'entire-emitted-initialized-section'})
            continue
        matches.append({'name': name, 'address': address, 'size': len(raw),
                        'data_hex': raw.hex(), 'source': relative,
                        'status': 'LINKED_DATA' if evidence else 'EXACT_DATA',
                        'sha256': hashlib.sha256(raw).hexdigest(),
                        'evidence': 'complete-section-with-original-bound-placement',
                        'relocations': evidence})
    if unresolved:
        # Keep the diagnostic, but no part of an unverified source object is
        # admitted as source data or executable code by the progress collector.
        return [], unresolved
    return matches, unresolved


def summarize(matches, unresolved):
    # Identical shared strings/tables may be emitted by several translation units.
    # Only their unique original bytes contribute to source-data coverage.
    covered = {}
    unique = {}
    for match in matches:
        raw, address = bytes.fromhex(match['data_hex']), match['address']
        for offset, value in enumerate(raw):
            location = address + offset
            if location in covered and covered[location] != value:
                raise ValueError('Conflicting verified data at ' + hex(location))
            covered[location] = value
        key = (address, len(raw), match['sha256'])
        if key not in unique:
            unique[key] = match
        else:
            unique[key].setdefault('additional_sources', []).append(match['source'])
    patches = sorted(unique.values(), key=lambda value: (value['address'], value['size']))
    report = {'verified_objects_or_sections': len(patches), 'compiled_data_bytes': len(covered),
              'unresolved_objects': unresolved, 'full_data_relink_complete': False,
              'note': 'Only complete matching compiler output is counted; unresolved and original preserved data are excluded.'}
    save_json(ROOT / 'build/reports/source_data_patches.json', patches)
    save_json(ROOT / 'build/reports/data_progress.json', report)
    return report

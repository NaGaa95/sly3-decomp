"""Resolve proven VU microprogram entry labels within their EE source only.

These labels inhabit VU instruction memory. They are neither EE data objects
nor decompiled VU functions. Every use still undergoes the usual complete EE
code, relocation and initialized-section comparison.
"""
import hashlib
import json
import struct
from pathlib import Path
from common import ROOT, Elf32, target_config


def source_vu_bindings(source, output, addresses, configuration=None):
    source = Path(source).resolve()
    try:
        relative = source.relative_to(ROOT).as_posix()
    except ValueError:
        return dict(addresses)
    if configuration is None:
        path = ROOT / 'config/object_vu_symbol_addrs.json'
        configuration = json.loads(path.read_text()) if path.exists() else {}
    scope = configuration.get(relative)
    if scope is None:
        return dict(addresses)
    if not isinstance(scope, dict) or set(scope) != {'address_space', 'proof', 'symbols'}:
        raise ValueError('Invalid source VU scope')
    if scope['address_space'] != 'VU microinstruction byte addresses':
        raise ValueError('Unsupported VU address space')
    reference = scope['proof']
    if not isinstance(reference, dict) or set(reference) != {'path', 'sha256'}:
        raise ValueError('Missing pinned VU entry proof')
    proof_path = (ROOT / reference['path']).resolve()
    if not any(proof_path.is_relative_to(ROOT / folder)
               for folder in ('config/proofs', 'build/reports')):
        raise ValueError('VU proof must be checked project metadata')
    raw = proof_path.read_bytes()
    if hashlib.sha256(raw).hexdigest() != reference['sha256']:
        raise ValueError('Changed VU entry proof')
    proof = json.loads(raw)
    if not proof['status'].startswith('PASS_COMPLETE408') or proof['EE_source_path'] != relative:
        raise ValueError('Unapproved or wrong-source VU entry proof')
    if proof['VU_program_source_progress_counted'] is not False:
        raise ValueError('VU binding proof cannot claim VU source completion')
    symbols = scope['symbols']
    if not isinstance(symbols, dict) or not symbols or symbols != proof['scoped_VU_absolute_bindings']:
        raise ValueError('VU symbols disagree with original upload proof')
    original_path = ROOT / 'disc' / target_config()['serial']
    original_raw = original_path.read_bytes()
    if hashlib.sha256(original_raw).hexdigest() != proof['original_main_sha256']:
        raise ValueError('Changed original game for VU upload proof')
    original = Elf32(original_raw)
    upload = proof['upload_scope']
    stream = original.at_vram(upload['begin'], upload['bytes'])
    section = original.section('.vutext')
    if not section['addr'] <= upload['begin'] < upload['begin'] + upload['bytes'] <= section['addr'] + section['size']:
        raise ValueError('VU upload lies outside original microprogram section')
    if hashlib.sha256(stream).hexdigest() != upload['sha256']:
        raise ValueError('Changed original VIF upload stream')
    micro = {}
    cursor = 0
    for packet in upload['packets']:
        if cursor + 8 > len(stream):
            raise ValueError('Truncated MPG command')
        nop, command = struct.unpack_from('<II', stream, cursor)
        count = ((command >> 16) & 0xff) or 256
        destination = (command & 0xffff) * 8
        if nop or (command >> 24) != 0x4a or destination + count * 8 > 0x4000:
            raise ValueError('Invalid MPG command or instruction-memory placement')
        size = count * 8
        payload = stream[cursor+8:cursor+8+size]
        if len(payload) != size or packet != {'command_address': upload['begin'] + cursor + 4,
                'destination': destination, 'instructions': count,
                'payload_sha256': hashlib.sha256(payload).hexdigest()}:
            raise ValueError('MPG placement disagrees with proof')
        for i, value in enumerate(payload):
            location = destination + i
            if location in micro:
                raise ValueError('Overlapping microprogram uploads')
            micro[location] = value
        cursor += 8 + size
    if cursor != len(stream):
        raise ValueError('Unreviewed trailing VIF commands')
    obj = Elf32(Path(output).read_bytes())
    definitions = obj.symbols()
    resolved = dict(addresses)
    for name, value in symbols.items():
        if not name.startswith('VU_') or name in addresses:
            raise ValueError('VU label overlaps global EE symbol namespace')
        candidates = [s for s in definitions if s['name'] == name]
        if len(candidates) != 1 or candidates[0]['shndx'] != 0 or candidates[0]['type'] not in (0, 1):
            raise ValueError('VU label must be a single undefined non-function symbol')
        symbol = candidates[0]
        uses = []
        for section in obj.sections:
            if section['type'] != 9:
                continue
            if not obj.sections[section['info']]['flags'] & 4:
                raise ValueError('VU source bindings cannot relocate initialized data')
            data = obj.section_data(section)
            for offset in range(0, len(data), section['entsize'] or 8):
                _, info = struct.unpack_from('<II', data, offset)
                if info >> 8 == symbol['index'] and section['link'] == symbol['table']:
                    uses.append(info & 255)
        if not uses or set(uses) != {5, 6}:
            raise ValueError('VU label is only supported as a paired native address operand')
        address = int(value, 0)
        if address < 0 or address % 8 or address >= 0x4000:
            raise ValueError('Invalid VU instruction byte address')
        entry = next((e for e in upload['entries'] if e['symbol'] == name), None)
        if entry is None or address != entry['address']:
            raise ValueError('Unreviewed VU entry label')
        try:
            body = bytes(micro[address + i] for i in range(entry['size']))
        except KeyError as error:
            raise ValueError('VU entry was not completely uploaded') from error
        if hashlib.sha256(body).hexdigest() != entry['sha256']:
            raise ValueError('VU entry bytes disagree with proof')
        resolved[name] = address
    return resolved

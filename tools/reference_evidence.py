"""Bind reference-source external operands without accepting a masked match."""
import struct
from collections import defaultdict
from common import Elf32
from relocate import sign16


def relocation_evidence(output, name, result):
    elf = Elf32(output.read_bytes())
    syms = elf.symbols()
    by_index = {(s["table"], s["index"]): s for s in syms}
    func = next(s for s in syms if s["name"] == name)
    evidence = []
    pending = defaultdict(list)
    bindings = {}
    deferred_lows = []
    for sec in elf.sections:
        if sec["type"] != 9 or sec["info"] != func["shndx"]: continue
        for pos in range(sec["offset"], sec["offset"] + sec["size"], 8):
            off, info = struct.unpack_from("<II", elf.data, pos)
            if not func["value"] <= off < func["value"] + func["size"]: continue
            index = (off - func["value"]) // 4
            sym = by_index[(sec["link"], info >> 8)]
            original = result["target"][index]
            compiled = result["compiled"][index]
            e = {"instruction": index, "type": info & 255, "symbol": sym["name"], "symbol_section": sym["shndx"], "symbol_value": sym["value"], "target_word": "0x%08X" % original, "object_word": "0x%08X" % compiled}
            if e["type"] == 4 and sym["shndx"] == 0:
                destination = ((result["address"] + index * 4 + 4) & 0xf0000000) | ((original & 0x3ffffff) << 2)
                addend = (compiled & 0x3ffffff) << 2
                if addend & 0x8000000: addend -= 0x10000000
                e["expected_address"] = "0x%08X" % ((destination - addend) & 0xffffffff)
            elif e["type"] == 5:
                pending[(sym["table"], sym["index"])].append(e)
            elif e["type"] == 6 and sym["shndx"] == 0:
                highs = pending.pop((sym["table"], sym["index"]), [])
                if not highs:
                    key = (sym['table'], sym['index'])
                    if key not in bindings:
                        deferred_lows.append((key,e))
                        evidence.append(e)
                        continue
                    value = bindings[key]
                    if (value + sign16(compiled)) & 65535 != original & 65535:
                        raise ValueError('Standalone LO16 disagrees with the established HI/LO binding')
                    e['expected_address'] = '0x%08X' % value
                    e['reused_verified_hi_lo_binding'] = True
                    evidence.append(e)
                    continue
                expected = set()
                for high in highs:
                    target_value = ((int(high["target_word"], 16) & 65535) << 16) + sign16(original)
                    object_addend = ((int(high["object_word"], 16) & 65535) << 16) + sign16(compiled)
                    value = (target_value - object_addend) & 0xffffffff
                    high["expected_address"] = "0x%08X" % value
                    expected.add(value)
                if len(expected) != 1: raise ValueError("Multiple HI16 references disagree")
                e["expected_address"] = "0x%08X" % expected.pop()
                key = (sym['table'], sym['index'])
                if key in bindings and bindings[key] != int(e['expected_address'],16):
                    raise ValueError('Contradictory HI/LO bindings for one external')
                bindings[key] = int(e['expected_address'],16)
            evidence.append(e)
    for key,e in deferred_lows:
        if key not in bindings:
            raise ValueError('Standalone LO16 is not independently resolvable')
        value = bindings[key]
        compiled, original = int(e['object_word'],16), int(e['target_word'],16)
        if (value + sign16(compiled)) & 65535 != original & 65535:
            raise ValueError('Standalone LO16 disagrees with the established HI/LO binding')
        e['expected_address'] = '0x%08X' % value
        e['reused_verified_hi_lo_binding'] = True
    return evidence


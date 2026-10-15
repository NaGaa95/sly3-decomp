"""Resolve ELF REL operands before claiming a byte-for-byte function match.

Implements the static non-PIC subset used by the checked EE objects. Unknown
symbols, unsupported relocations and unpaired HI16 records fail closed.
See https://refspecs.linuxfoundation.org/elf/mipsabi.pdf, chapter 4.
"""
import re
import struct
from pathlib import Path
from common import ROOT, Elf32, target_config


class RelocationError(ValueError):
    pass


def symbol_addresses():
    addresses = {}
    for line in (ROOT / "config/symbol_addrs.txt").read_text().splitlines():
        match = re.match(r"(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if match:
            name, address = match[1], int(match[2], 16)
            if name in addresses and addresses[name] != address:
                raise RelocationError("Conflicting symbol: " + name)
            addresses[name] = address
    # Provisional function names have their address encoded; only indexed names
    # are admitted by the caller's known-functions map.
    from matchtool import functions
    addresses.update({name: value[0] for name, value in functions().items() if name not in addresses})
    return addresses


def sign16(value):
    return (value & 0x7fff) - (value & 0x8000)


class ObjectLinker:
    def __init__(self, path, addresses=None, placements=None, target=None):
        self.path = Path(path)
        self.elf = Elf32(self.path.read_bytes())
        self.addresses = symbol_addresses() if addresses is None else addresses
        self.placements = dict(placements or {})
        self.target = target or Elf32((ROOT / "disc" / target_config()["serial"]).read_bytes())
        self.symbols = self.elf.symbols()
        self.by_index = {(s["table"], s["index"]): s for s in self.symbols}
        self.funcs = [s for s in self.symbols if s["type"] == 2 and s["size"] and s["shndx"] < len(self.elf.sections)]
        self.relocations = {}
        for section in self.elf.sections:
            if section["type"] == 4:
                raise RelocationError("RELA is not supported")
            if section["type"] != 9:
                continue
            entries = self.relocations.setdefault(section["info"], [])
            for offset in range(section["offset"], section["offset"] + section["size"], section["entsize"] or 8):
                place, info = struct.unpack_from("<II", self.elf.data, offset)
                entries.append({"offset": place, "kind": info & 255, "symbol": self.by_index[(section["link"], info >> 8)]})
        self.data_matches = []
        self._locate_constant_sections()
        self._locate_referenced_constants()

    def _locate_constant_sections(self):
        # Constants must match actual original bytes uniquely, not just the
        # immediates in referencing instructions. Relocated tables need explicit
        # placement and are deliberately excluded from this discovery step.
        for section in self.elf.sections:
            if section["name"] not in (".rodata", ".sdata", ".data", ".lit4", ".lit8") or not section["size"] or self.relocations.get(section["index"]):
                continue
            raw = self.elf.section_data(section)
            # Whole zero sections and short scalars are too ambiguous.
            if len(raw) < 8 or not any(raw) or section["name"] in self.placements:
                continue
            matches = []
            for original in self.target.sections:
                if original["name"] not in (".rodata", ".data", ".sdata", ".lit4", ".lit8"):
                    continue
                haystack = self.target.section_data(original)
                offset = haystack.find(raw)
                while offset >= 0 and len(matches) < 2:
                    address = original["addr"] + offset
                    if address % max(1, section["alignment"]) == 0:
                        matches.append(address)
                    offset = haystack.find(raw, offset + 1)
            if len(matches) == 1:
                self.placements[section["name"]] = matches[0]
                self.data_matches.append({"section": section["name"], "address": matches[0], "size": len(raw)})

    def _locate_referenced_constants(self):
        # Duplicated constants can still be bound by original HI/LO operands,
        # provided the complete compiled section matches at that exact address.
        # An address match alone never validates a different constant/table.
        candidates = {}
        for section_index, records in self.relocations.items():
            # Placement evidence comes from original code address operands.
            if not self.elf.sections[section_index]["flags"] & 4:
                continue
            pending = []
            section_raw = self.elf.section_data(self.elf.sections[section_index])
            for record in records:
                if record["kind"] == 5:
                    pending.append(record)
                    continue
                if record["kind"] != 6:
                    continue
                symbol = record["symbol"]
                if not 0 < symbol["shndx"] < len(self.elf.sections):
                    continue
                data_section = self.elf.sections[symbol["shndx"]]
                if data_section["name"] not in (".rodata", ".data", ".sdata", ".lit4", ".lit8") or not data_section["size"]:
                    continue
                if data_section["type"] != 1 or not data_section["flags"] & 2 or data_section["flags"] & 4:
                    continue
                paired = [high for high in pending if (high["symbol"]["table"], high["symbol"]["index"]) == (symbol["table"], symbol["index"])]
                for high in paired:
                    pending.remove(high)
                    try:
                        high_place = self.section_location(section_index, high["offset"])
                        low_place = self.section_location(section_index, record["offset"])
                        original_high = struct.unpack("<I", self.target.at_vram(high_place, 4))[0]
                        original_low = struct.unpack("<I", self.target.at_vram(low_place, 4))[0]
                        object_high = struct.unpack_from("<I", section_raw, high["offset"])[0]
                        object_low = struct.unpack_from("<I", section_raw, record["offset"])[0]
                        value = ((original_high & 0xffff) << 16) + sign16(original_low)
                        addend = ((object_high & 0xffff) << 16) + sign16(object_low)
                        base = (value - addend - symbol["value"]) & 0xffffffff
                    except (RelocationError, ValueError):
                        continue
                    # Keep rejected bindings too: a contradictory operand must
                    # not be hidden by another reference to identical constants.
                    candidates.setdefault(data_section["name"], []).append(base)
        for name, bindings in candidates.items():
            if name in self.placements:
                continue
            if len(set(bindings)) == 1:
                base = bindings[0]
                section = self.elf.section(name)
                if base % max(1, section["alignment"]):
                    continue
                # Tentative placement is required for a relocated whole section.
                # Local code pointers resolve through mapped STT_FUNC ranges;
                # every byte and every relocation must then equal the original.
                self.placements[name] = base
                try:
                    raw, evidence = self.constant_section(name)
                    original = next((s for s in self.target.sections
                                     if s["type"] == 1 and s["flags"] & 2 and not s["flags"] & 4
                                     and s["addr"] <= base and base + len(raw) <= s["addr"] + s["size"]), None)
                    valid = original is not None and self.target.at_vram(base, len(raw)) == raw
                except (RelocationError, ValueError):
                    valid = False
                if not valid:
                    del self.placements[name]
                    continue
                self.data_matches.append({"section": name, "address": base, "size": section["size"],
                                          "evidence": "original-address-operands-and-complete-relocated-constant-bytes" if evidence
                                                      else "original-address-operands-and-complete-constant-bytes"})

    def constant_section(self, name):
        """Resolve the complete initialized section, including local code pointers."""
        if name not in self.placements:
            raise RelocationError("No placement for constant section: " + name)
        section = self.elf.section(name)
        if section["type"] != 1 or not section["flags"] & 2 or section["flags"] & 4:
            raise RelocationError("Constant section is not allocated initialized data")
        symbol = {"shndx": section["index"], "value": 0, "size": section["size"]}
        return self._relocate_symbol(symbol, self.placements[name])

    def section_location(self, section_index, offset):
        section = self.elf.sections[section_index]
        if section["name"] in self.placements:
            return self.placements[section["name"]] + offset
        for function in self.funcs:
            if function["shndx"] == section_index and function["value"] <= offset < function["value"] + function["size"] and function["name"] in self.addresses:
                return self.addresses[function["name"]] + offset - function["value"]
        raise RelocationError(f"No placement for {section['name']}+0x{offset:X}")

    def symbol_value(self, symbol, addend=0):
        if symbol["type"] == 3:  # STT_SECTION: the addend is a section offset.
            return self.section_location(symbol["shndx"], symbol["value"] + addend)
        if symbol["name"] in self.addresses:
            return self.addresses[symbol["name"]] + addend
        if symbol["shndx"] == 0xfff1:  # SHN_ABS
            return symbol["value"] + addend
        if 0 < symbol["shndx"] < len(self.elf.sections):
            return self.section_location(symbol["shndx"], symbol["value"] + addend)
        raise RelocationError("Unresolved symbol: " + symbol["name"])

    def function(self, name):
        if name not in self.addresses:
            raise RelocationError("No original address for function: " + name)
        symbol = next(s for s in self.funcs if s["name"] == name)
        return self._relocate_symbol(symbol, self.addresses[name])

    def data_object(self, name):
        """Relocate a defined named object at its independently bound address."""
        if name not in self.addresses:
            raise RelocationError("No original address for data object: " + name)
        symbol = next((s for s in self.symbols if s["name"] == name and s["type"] == 1 and s["size"]), None)
        if symbol is None or not 0 < symbol["shndx"] < len(self.elf.sections):
            raise RelocationError("Not a defined initialized data object: " + name)
        section = self.elf.sections[symbol["shndx"]]
        if section["type"] != 1 or not section["flags"] & 2 or section["flags"] & 4:
            raise RelocationError("Data object is not in allocated initialized data: " + name)
        return self._relocate_symbol(symbol, self.addresses[name])

    def _relocate_symbol(self, symbol, address):
        section = self.elf.sections[symbol["shndx"]]
        start, end = symbol["value"], symbol["value"] + symbol["size"]
        raw = bytearray(self.elf.section_data(section)[start:end])
        if len(raw) != symbol["size"]:
            raise RelocationError("Symbol exceeds section")
        records = [r for r in self.relocations.get(section["index"], []) if start <= r["offset"] < end]
        pending = []
        evidence = []
        seen = set()
        def read(record):
            offset = record["offset"] - start
            if offset % 4 or offset + 4 > len(raw):
                raise RelocationError("Relocation is not a complete instruction")
            return struct.unpack_from("<I", raw, offset)[0]
        def write(record, value):
            struct.pack_into("<I", raw, record["offset"] - start, value & 0xffffffff)
        def patch(record, value, low=True):
            word = read(record)
            write(record, (word & 0xffff0000) | (value & 0xffff) if low else value)
            evidence.append({"offset": record["offset"] - start, "type": record["kind"], "symbol": record["symbol"]["name"], "value": value & 0xffffffff})
        for record in records:
            offset, kind, referenced = record["offset"], record["kind"], record["symbol"]
            if offset in seen:
                raise RelocationError("Multiple relocations at one instruction")
            seen.add(offset)
            word = read(record)
            if kind == 0:
                continue
            if kind == 5:  # R_MIPS_HI16
                pending.append(record)
                continue
            if kind == 6:  # R_MIPS_LO16, including standalone low references
                low = sign16(word)
                matching = [r for r in pending if (r["symbol"]["table"], r["symbol"]["index"]) == (referenced["table"], referenced["index"])]
                values = []
                for high in matching:
                    value = self.symbol_value(referenced, ((read(high) & 0xffff) << 16) + low)
                    patch(high, (value + 0x8000) >> 16)
                    values.append(value)
                    pending.remove(high)
                if matching:
                    if len({v & 0xffff for v in values}) != 1:
                        raise RelocationError("HI16 references disagree on LO16")
                    patch(record, values[0])
                else:
                    patch(record, self.symbol_value(referenced, low))
            elif kind == 4:  # R_MIPS_26
                addend = (word & 0x03ffffff) << 2
                if referenced["type"] != 3 and addend & 0x08000000:
                    addend -= 0x10000000
                value = self.symbol_value(referenced, addend)
                place = address + offset - start
                if value % 4 or (value & 0xf0000000) != ((place + 4) & 0xf0000000):
                    raise RelocationError("Jump target out of region/alignment")
                patch(record, (word & 0xfc000000) | ((value >> 2) & 0x03ffffff), False)
            elif kind == 2:  # R_MIPS_32
                patch(record, self.symbol_value(referenced, word), False)
            elif kind == 1:  # R_MIPS_16
                value = self.symbol_value(referenced, sign16(word))
                if not -0x8000 <= value <= 0x7fff:
                    raise RelocationError("R_MIPS_16 overflow")
                patch(record, value)
            else:
                raise RelocationError(f"Unsupported static relocation: {kind}")
        if pending:
            raise RelocationError("Unpaired HI16 relocation")
        return bytes(raw), evidence

"""Small checked ELF/ISO readers shared by the local preparation tools."""
from __future__ import annotations

import hashlib
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SECTOR = 2048


def save_json(path: Path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")


def sha256_file(path: Path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(8 * 1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def target_config():
    return json.loads((ROOT / "config/target.json").read_text(encoding="utf-8"))


class Elf32:
    def __init__(self, data: bytes):
        self.data = data
        if len(data) < 52 or data[:7] != b"\x7fELF\x01\x01\x01":
            raise ValueError("Expected an ELF32 little-endian executable/object")
        h = struct.unpack_from("<16sHHIIIIIHHHHHH", data)
        self.type, self.machine, self.entry = h[1], h[2], h[4]
        self.phoff, self.shoff, self.flags = h[5:8]
        self.phentsize, self.phnum = h[9:11]
        self.shentsize, self.shnum, self.shstrndx = h[11:14]
        if self.machine != 8:
            raise ValueError("Expected a MIPS ELF")
        if self.phnum and self.phentsize < 32:
            raise ValueError("Invalid program-header size")
        if self.shnum and self.shentsize < 40:
            raise ValueError("Invalid section-header size")
        self.sections = []
        keys = ("name_offset", "type", "flags", "addr", "offset", "size", "link", "info", "alignment", "entsize")
        for index in range(self.shnum):
            values = struct.unpack_from("<10I", data, self.shoff + index * self.shentsize)
            section = dict(zip(keys, values))
            section["index"] = index
            self.sections.append(section)
        names = self.section_data(self.sections[self.shstrndx]) if self.sections else b""
        for section in self.sections:
            start = section["name_offset"]
            section["name"] = names[start:].split(b"\0", 1)[0].decode("ascii", errors="replace")
            if section["type"] != 8 and section["offset"] + section["size"] > len(data):
                raise ValueError("Section outside ELF: " + section["name"])
        self.program_headers = []
        for i in range(self.phnum):
            values = struct.unpack_from("<8I", data, self.phoff + i * self.phentsize)
            self.program_headers.append(dict(zip(("type", "offset", "vaddr", "paddr", "filesz", "memsz", "flags", "alignment"), values)))

    def section(self, name):
        return next(s for s in self.sections if s["name"] == name)

    def section_data(self, section):
        if section["type"] == 8:
            return b""
        return self.data[section["offset"]:section["offset"] + section["size"]]

    def at_vram(self, address, size):
        for s in self.sections:
            if s["type"] != 8 and s["addr"] <= address and address + size <= s["addr"] + s["size"]:
                offset = s["offset"] + address - s["addr"]
                return self.data[offset:offset + size]
        raise ValueError(f"Unmapped ELF range 0x{address:X}+0x{size:X}")

    def symbols(self):
        symbols = []
        for section in self.sections:
            if section["type"] != 2:
                continue
            strings = self.section_data(self.sections[section["link"]])
            for offset in range(section["offset"], section["offset"] + section["size"], section["entsize"] or 16):
                name, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", self.data, offset)
                symbols.append({"name": strings[name:].split(b"\0", 1)[0].decode("ascii", errors="replace"), "value": value, "size": size, "type": info & 15, "binding": info >> 4, "visibility": other, "shndx": shndx, "table": section["index"], "index": (offset - section["offset"]) // (section["entsize"] or 16)})
        return symbols


class Iso9660:
    def __init__(self, path):
        self.path = Path(path).resolve()
        self.stream = self.path.open("rb")
        self.size = self.path.stat().st_size
        pvd = self.read_at(16 * SECTOR, SECTOR)
        if pvd[:7] != b"\x01CD001\x01" or struct.unpack_from("<H", pvd, 128)[0] != SECTOR:
            raise ValueError("Expected an ISO9660 image with 2048-byte sectors")
        self.volume_id = pvd[40:72].decode("ascii", errors="replace").strip()
        self.entries = []
        self._walk(self._record(pvd[156:156 + pvd[156]]), Path(), set())

    def read_at(self, offset, size):
        if offset < 0 or size < 0 or offset + size > self.size:
            raise ValueError("Read outside ISO")
        self.stream.seek(offset)
        data = self.stream.read(size)
        if len(data) != size:
            raise ValueError("Truncated ISO")
        return data

    @staticmethod
    def _record(record):
        if len(record) < 34:
            raise ValueError("Invalid ISO directory record")
        return {"lba": struct.unpack_from("<I", record, 2)[0], "size": struct.unpack_from("<I", record, 10)[0], "flags": record[25], "name": record[33:33 + record[32]].decode("ascii")}

    def _walk(self, directory, prefix, visited):
        if directory["lba"] in visited:
            raise ValueError("Cyclic ISO directory")
        visited.add(directory["lba"])
        data = self.read_at(directory["lba"] * SECTOR, directory["size"])
        offset = 0
        while offset < len(data):
            length = data[offset]
            if not length:
                offset = (offset // SECTOR + 1) * SECTOR
                continue
            record = self._record(data[offset:offset + length])
            offset += length
            if record["name"] in ("\0", "\1"):
                continue
            name = record["name"].split(";", 1)[0]
            if name in (".", "..") or any(c in name for c in ("/", "\\", ":")):
                raise ValueError("Unsafe ISO path component")
            if record["flags"] & 0x80:
                raise ValueError("Multi-extent ISO files are not supported")
            record["path"] = (prefix / name).as_posix()
            if record["flags"] & 2:
                self._walk(record, prefix / name, visited)
            else:
                if record["lba"] * SECTOR + record["size"] > self.size:
                    raise ValueError("File outside ISO")
                self.entries.append(record)

    def close(self):
        self.stream.close()

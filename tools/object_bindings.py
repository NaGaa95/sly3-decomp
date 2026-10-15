"""Bind compiler-generated function names within one source object only.

Local initialization helpers can share names across translation units. GCC also
puts its temporary filename in initializer wrappers. These are explicit source
placements, never global aliases or inferred function lengths. Every resulting
function still has to match the complete indexed original body after relocation.
"""
import json
from pathlib import Path
from common import ROOT, Elf32


def source_bindings(source, output, known, addresses, configuration=None):
    source = Path(source).resolve()
    try:
        relative = source.relative_to(ROOT).as_posix()
    except ValueError:
        return dict(known), dict(addresses)
    if configuration is None:
        path = ROOT / "config/object_symbol_addrs.json"
        configuration = json.loads(path.read_text()) if path.exists() else {}
    entries = configuration.get(relative, {})
    from vu_object_bindings import source_vu_bindings
    local_known = dict(known)
    local_addresses = source_vu_bindings(source, output, addresses)
    if not entries:
        return local_known, local_addresses
    if not isinstance(entries, dict):
        raise ValueError("Source symbol bindings must be a dictionary: " + relative)
    elf = Elf32(Path(output).read_bytes())
    defined = [symbol for symbol in elf.symbols() if symbol["type"] == 2 and symbol["size"]
               and 0 < symbol["shndx"] < len(elf.sections)
               and elf.sections[symbol["shndx"]]["flags"] & 4]
    by_address = {}
    for address, size in known.values():
        if address in by_address and by_address[address] != size:
            raise ValueError("Contradictory indexed function sizes")
        by_address[address] = size
    assigned = set()
    for selector, original in entries.items():
        if not isinstance(selector, str) or not isinstance(original, str):
            raise ValueError("Invalid source symbol binding")
        if "*" in selector:
            if selector.count("*") != 1 or not selector.endswith("*") or len(selector) < 2:
                raise ValueError("Only a nonempty trailing symbol prefix is supported")
            candidates = [symbol for symbol in defined if symbol["name"].startswith(selector[:-1])]
        else:
            candidates = [symbol for symbol in defined if symbol["name"] == selector]
        if len(candidates) != 1:
            raise ValueError(f"Scoped symbol {relative}:{selector} resolves to {len(candidates)} functions")
        symbol = candidates[0]
        address = int(original, 0)
        if address not in by_address:
            raise ValueError("Scoped symbol address has no indexed original function: " + original)
        name = symbol["name"]
        if name in assigned:
            raise ValueError("Scoped function is selected more than once: " + name)
        if name in local_addresses and local_addresses[name] != address:
            raise ValueError("Scoped binding conflicts with a global symbol: " + name)
        assigned.add(name)
        local_addresses[name] = address
        local_known[name] = (address, by_address[address])
    return local_known, local_addresses

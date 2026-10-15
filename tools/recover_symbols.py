"""Merge consistent Sly 3 symbol evidence from independently compared sources.

Decoded call targets identify external function locations, not proof that the
external function is decompiled. HI/LO pairs identify referenced data addresses.
Conflicting and section-relative names are never assigned a global alias.
"""
import json
import re
from collections import defaultdict
from common import ROOT, save_json
from relocate import sign16


def main():
    proposals = defaultdict(lambda: defaultdict(list))
    for filename in ("engine_symbols.txt", "hand_symbols.txt", "lib_symbols.txt", "newlib_stdlib_agent_symbols.txt", "libgcc_agent_symbols.txt", "string_agent_symbols.txt", "runtime_agent_symbols.txt", "wrapper_symbols.txt", "auto_symbols.txt", "math_symbols.txt", "reference_symbols.txt", "reference_cpp_symbols.txt", "reference_os_symbols.txt", "reference_constant_symbols.txt", "startup_symbols.txt", "game_middle_symbols.txt"):
        path = ROOT / "build/reports" / filename
        if not path.exists():
            continue
        for line in path.read_text().splitlines():
            match = re.match(r"(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
            if match:
                proposals[match[1]][int(match[2], 16)].append({"kind": "function-identification", "report": filename})
    for filename in ("leaf_matches.json", "lib_matches.json", "newlib_stdlib_matches.json", "newlib_stdlib_agent_matches.json", "libgcc_agent_matches.json", "string_agent_matches.json", "runtime_agent_matches.json", "wrapper_matches.json", "auto_matches.json", "math_matches.json", "reference_matches.json", "reference_cpp_matches.json", "reference_os_matches.json", "reference_constant_matches.json", "factory_matches.json", "game_middle_matches.json"):
        path = ROOT / "build/reports" / filename
        if not path.exists():
            continue
        for function in json.loads(path.read_text())["functions"]:
            if function["status"] not in ("EXACT_MATCH", "NORMALIZED_MATCH", "LINKED_MATCH"):
                continue
            records = function.get("relocation_evidence", [])
            pending = []
            for record in records:
                # Fully linked evidence describes the output, not independently
                # decoded original/object operands. It cannot propose aliases.
                if "target_word" not in record or "object_word" not in record:
                    continue
                symbol, kind = record["symbol"], record["type"]
                if not symbol or symbol.startswith(".") or symbol.startswith("$"):
                    continue
                if symbol in function.get("symbol_address_spaces", {}):
                    continue  # VU entries belong to their reviewed object scope.
                if kind == 4 and record.get("expected_address"):
                    proposals[symbol][int(record["expected_address"], 16)].append({"kind": "call-target", "function": function["name"], "instruction": record["instruction"]})
                elif kind == 5:
                    pending.append(record)
                elif kind == 6:
                    matching = [high for high in pending if high["symbol"] == symbol]
                    for high in matching:
                        target = ((int(high["target_word"], 16) & 0xffff) << 16) + sign16(int(record["target_word"], 16))
                        addend = ((int(high["object_word"], 16) & 0xffff) << 16) + sign16(int(record["object_word"], 16))
                        address = (target - addend) & 0xffffffff
                        proposals[symbol][address].append({"kind": "data-address-pair", "function": function["name"], "instruction": high["instruction"]})
                        pending.remove(high)
    path = ROOT / "config/symbol_addrs.txt"
    existing = {}
    for line in path.read_text().splitlines():
        match = re.match(r"(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if match:
            existing[match[1]] = int(match[2], 16)
    conflicts, added, evidence = {}, {}, []
    for name, targets in sorted(proposals.items()):
        canonical = re.fullmatch(r"func_([0-9A-Fa-f]{8})", name)
        if len(targets) != 1 or (canonical and next(iter(targets)) != int(canonical[1], 16)):
            conflicts[name] = [f"0x{a:08X}" for a in targets]
            continue
        address = next(iter(targets))
        if name in existing and existing[name] != address:
            conflicts[name] = [f"0x{existing[name]:08X}", f"0x{address:08X}"]
            continue
        if name not in existing:
            added[name] = address
        evidence.append({"name": name, "address": f"0x{address:08X}", "evidence": targets[address]})
    with path.open("a", encoding="utf-8") as stream:
        if added:
            stream.write("\n// Sly 3 addresses recovered from compared source definitions and call/data operands.\n")
            for name, address in sorted(added.items()):
                stream.write(f"{name} = 0x{address:08X};\n")
    save_json(ROOT / "build/reports/symbol_recovery.json", {"added": len(added), "conflicts": conflicts, "symbols": evidence})
    print(f"Merged {len(added)} consistent symbols; withheld {len(conflicts)} conflicts")


if __name__ == "__main__":
    main()

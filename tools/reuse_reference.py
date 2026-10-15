"""Recover reference functions, bind original operands, then verify all bytes."""
import csv
import json
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import Elf32
from compiler import compile_source
from matchtool import functions, object_functions, compare, compare_object
from relocate import ObjectLinker, sign16

known = functions()
all_rows = list(csv.DictReader((ROOT / "build/reports/sly2_address_candidates.csv").open()))
cpp = "--cpp" in sys.argv
cohort = "reference_cpp" if cpp else "reference"
report_path = ROOT / "build/reports" / (cohort + "_matches.json")
stage = ROOT / "build" / (cohort + "_matches/source")
stage.mkdir(parents=True, exist_ok=True)
(ROOT / "src" / cohort).mkdir(parents=True, exist_ok=True)
ambiguous = "--ambiguous-auto-only" in sys.argv
repair = "--repair-definitions" in sys.argv
retry = "--retry" in sys.argv
report = json.loads(report_path.read_text())["functions"] if (ambiguous or repair or retry) and report_path.exists() else []
retry_names = {item['name'] for item in report if item['status'] in ('COMPILE_ERROR', 'DIFFERENT', 'UNRESOLVED_RELOCATION')}
if retry:
    report = [item for item in report if item['name'] not in retry_names]
repair_names = {item["name"] for item in report if item["status"] == "DEFINITION_NOT_FOUND"}
if repair: report = [item for item in report if item["name"] not in repair_names]
aliases = defaultdict(set)
reserved = set()
for previous in report:
    for e in previous.get("relocation_evidence", []):
        if previous.get("source") and e["symbol_section"] == 0 and "expected_address" in e:
            aliases[e["symbol"]].add(int(e["expected_address"], 16))
for path in (ROOT / "build/reports/leaf_matches.json", ROOT / "build/reports/engine_matches.json", ROOT / "build/reports/reference_matches.json", ROOT / "build/reports/reference_cpp_matches.json", ROOT / "build/reports/lib_matches.json"):
    if not path.exists(): continue
    prior = json.loads(path.read_text())
    prior = prior["functions"] if isinstance(prior, dict) else prior
    for item in prior:
        if item.get("source") and item.get("status") in ("EXACT_MATCH", "NORMALIZED_MATCH", "LINKED_MATCH"):
            reserved.add(int(item["address"], 0) if isinstance(item["address"], str) else item["address"])
matched = {int(row["address"],16) for row in csv.DictReader((ROOT/"config/matched.csv").open())}
reserved.update(matched)
grouped={}
for row in all_rows:
    if retry and row['Sly3Name'] not in retry_names: continue
    extensions = (".cpp", ".cc") if cpp else (".c",)
    if int(row["Sly3Address"],16) in reserved or not row["Sly2Source"].endswith(extensions): continue
    path=ROOT/"references/sly2"/row["Sly2Source"]
    if re.search(r"__asm|\basm\b",path.read_text()):continue
    grouped.setdefault(row["Sly3Name"],row)
rows=list(grouped.values())

def write_report():
    temporary = report_path.with_suffix(".tmp.json")
    temporary.write_text(json.dumps({"counts": dict(Counter(r["status"] for r in report)), "functions": report}, indent=2) + "\n")
    temporary.replace(report_path)
    (ROOT / "build/reports" / (cohort + "_symbols.txt")).write_text("\n".join("%s = 0x%08X;" % (name, next(iter(values))) for name, values in sorted(aliases.items()) if len(values) == 1) + "\n")

from reference_evidence import relocation_evidence

for batch_index, row in enumerate(rows):
    name, oldname = row["Sly3Name"], row["Sly2Name"]
    item = {"name": name, "address": row["Sly3Address"], "object_symbol": name, "reference": row["Sly2Source"], "reference_symbol": oldname, "reference_identity_ambiguous": row["Ambiguous"] == "True"}
    if int(row["Sly3Address"], 16) in reserved or 0x118B00 <= int(row["Sly3Address"], 16) < 0x119600:
        item["status"] = "RESERVED_SUBSYSTEM"
        report.append(item)
        continue
    original = ROOT / "references/sly2" / row["Sly2Source"]
    text = original.read_text().replace("splicewrap.h","recovered/splicewrap.h")
    if re.search(r"__asm|\basm\b", text):
        item["status"] = "DEFERRED_INLINE_ASM"
        report.append(item)
        continue
    if original.suffix not in extensions:
        item["status"] = "DEFERRED_NON_C"
        report.append(item)
        continue
    source_name = oldname
    if not re.search(r"\b" + re.escape(source_name) + r"\s*\([^;{}]*\)\s*\{", text) and re.search(r"\b" + re.escape(original.stem) + r"\s*\([^;{}]*\)\s*\{", text):
        source_name = original.stem
        item["source_definition"] = source_name
    if not re.search(r"\b" + re.escape(source_name) + r"\s*\([^;{}]*\)\s*\{", text):
        item["status"] = "DEFINITION_NOT_FOUND"
        report.append(item)
        continue
    text = re.sub(r"\b" + re.escape(source_name) + r"\b", name, text)
    text = "// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.\n" + text
    source = stage / (name + original.suffix)
    source.write_text(text)
    output = ROOT / "build" / (cohort + "_matches/obj") / (name + ".o")
    item["object"] = output.relative_to(ROOT).as_posix()
    try:
        compile_source(source, output)
        code, rel = object_functions(output)[name]
        result = compare(name, code, rel, known=known)
        item.update({k: result[k] for k in ("status", "instructions", "relocations", "differences")})
        if item["status"] not in ("EXACT_MATCH", "NORMALIZED_MATCH"):
            draft = ROOT / "build/hand_wip/reference" / source.name
            draft.parent.mkdir(parents=True, exist_ok=True)
            draft.write_text(text)
        else:
            evidence = relocation_evidence(output, name, result)
            replacements = {}
            inferred = defaultdict(set)
            for e in evidence:
                if e["symbol_section"] != 0: continue
                if "expected_address" not in e: raise ValueError("Cannot resolve external " + e["symbol"])
                expected = int(e["expected_address"], 16)
                inferred[e["symbol"]].add(expected)
                replacements[e["symbol"]] = ("func_" if e["type"] == 4 else "D_") + "%08X" % expected
            if any(len(values) != 1 for values in inferred.values()):
                raise ValueError("One source external name refers to multiple original addresses")
            if replacements:
                text = re.sub(r"\b[A-Za-z_][A-Za-z_0-9]*\b", lambda m: replacements.get(m[0], m[0]), text)
                source.write_text(text)
                compile_source(source, output)
                code, rel = object_functions(output)[name]
                result = compare(name, code, rel, known=known)
                if result["status"] not in ("EXACT_MATCH", "NORMALIZED_MATCH"):
                    raise ValueError("Renamed source changed instruction shape")
                evidence = relocation_evidence(output, name, result)
                item["extern_replacements"] = replacements
            item["relocation_evidence"] = evidence
            addresses = {symbol: addr for symbol, (addr, size) in known.items()}
            for e in evidence:
                if e["symbol_section"] == 0 and "expected_address" in e:
                    addresses[e["symbol"]] = int(e["expected_address"], 16)
            linker = ObjectLinker(output, addresses=addresses)
            strict = compare_object(name, output, known=known, linker=linker)
            item["strict_status"] = strict["status"]
            if strict["status"] not in ("EXACT_MATCH", "LINKED_MATCH"):
                item["strict_reason"] = strict.get("reason", "")
                item["strict_differences"] = strict.get("differences", [])
                item["status"] = "UNRESOLVED_RELOCATION" if strict["status"] == "UNRESOLVED_RELOCATION" else "DIFFERENT"
                draft = ROOT / "build/hand_wip/reference" / source.name
                draft.parent.mkdir(parents=True, exist_ok=True)
                draft.write_text(text)
            else:
                item["status"] = strict["status"]
                extra = set(object_functions(output)) - {name}
                if extra:
                    raise ValueError("Additional emitted functions require independent recovery: " + ", ".join(sorted(extra)))
                destination = ROOT / "src" / cohort / source.name
                destination.write_text(text)
                item["source"] = destination.relative_to(ROOT).as_posix()
                for e in evidence:
                    if e["symbol_section"] == 0 and "expected_address" in e:
                        aliases[e["symbol"]].add(int(e["expected_address"], 16))
    except Exception as exc:
        item["status"] = "COMPILE_ERROR"
        item["error"] = str(exc)
        item["stderr"] = getattr(exc, "stderr", "")
        draft = ROOT / "build/hand_wip/reference" / source.name
        draft.parent.mkdir(parents=True, exist_ok=True)
        draft.write_text(source.read_text())
    report.append(item)
    write_report()
    print("%d/%d %s %s" % (batch_index + 1, len(rows), name, item["status"]), flush=True)
write_report()
print(dict(Counter(r["status"] for r in report)))

"""Import independently compared SDK candidates from the local Sly 2 reference.

Only instruction-shape matches are staged as source; definitive progress is
collected separately after original Sly 3 symbol addresses are resolved.
"""
import csv
import argparse
import json
import re
import subprocess
from collections import Counter
from common import ROOT, save_json, Elf32, target_config
from compiler import compile_source
from matchtool import functions, object_functions, compare
from object_evidence import function_evidence


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--candidates", default="build/reports/sly2_candidates.csv")
    args = parser.parse_args()
    candidates = list(csv.DictReader((ROOT / args.candidates).open()))
    known = functions()
    original = Elf32((ROOT / "disc" / target_config()["serial"]).read_bytes())
    sources = {}
    for row in candidates:
        if row["Ambiguous"] == "False" and row["Sly2Source"].startswith("src/lib/"):
            sources.setdefault(row["Sly3Name"], row)
    report_path = ROOT / "build/reports/lib_matches.json"
    results = json.loads(report_path.read_text())["functions"] if report_path.exists() else []
    aliases_path = ROOT / "build/reports/lib_symbols.txt"
    aliases = [aliases_path.read_text()] if aliases_path.exists() else []
    existing = {r["name"] for r in results}
    for name, row in sources.items():
        if name in existing:
            continue
        reference = ROOT / "references/sly2" / row["Sly2Source"]
        text = reference.read_text(encoding="utf-8")
        result = {"name": name, "address": row["Sly3Address"], "reference": row["Sly2Source"], "reference_symbol": row["Sly2Name"]}
        if re.search(r"\b(?:asm|__asm__)\s*(?:__volatile__\s*)?\(", text):
            result["status"] = "DEFERRED_INLINE_ASM"
            results.append(result)
            continue
        if "SLY2_ASM: gnu-reorder" in text:
            result["status"] = "DEFERRED_ASSEMBLER_PROFILE"
            results.append(result)
            continue
        text = text.replace("SLY2_", "SLY3_").replace("tools/compilers/bundle/", "tools/third_party/")
        compiler = re.search(r"SLY3_CC:\s*(\S+)", text)
        if compiler and not (ROOT / compiler[1]).exists():
            result["status"] = "DEFERRED_COMPILER_PROFILE"
            results.append(result)
            continue
        symbol = row["Sly2Name"]
        if symbol.startswith("func_"):
            text = re.sub(r"\b" + re.escape(symbol) + r"\b", name, text)
            symbol = name
        source = ROOT / "src/lib" / (name + reference.suffix)
        source.write_text("// Reference: Sly 2 " + row["Sly2Source"] + "; target Sly 3 " + row["Sly3Address"] + ".\n" + text, encoding="utf-8")
        output = ROOT / "build/lib_matches" / (name + ".o")
        try:
            compile_source(source, output)
            objects = object_functions(output)
            if symbol not in objects:
                raise ValueError("Expected definition not found: " + symbol)
            local_known = dict(known)
            local_known[symbol] = known[name]
            compared = compare(symbol, *objects[symbol], original, local_known)
            result.update({key: value for key, value in compared.items() if key not in ("target", "compiled", "differences", "address", "name")})
            result["object_symbol"] = symbol
            result["object"] = output.relative_to(ROOT).as_posix()
            result["relocation_evidence"] = function_evidence(output, symbol, int(row["Sly3Address"], 16))
            if compared["status"] in ("EXACT_MATCH", "NORMALIZED_MATCH"):
                result["source"] = source.relative_to(ROOT).as_posix()
                aliases.append(f"{symbol} = {row['Sly3Address']}; // type:func\n")
            else:
                draft = ROOT / "build/hand_wip/lib" / source.name
                draft.parent.mkdir(parents=True, exist_ok=True)
                source.replace(draft)
        except (subprocess.CalledProcessError, ValueError) as error:
            result["status"] = "COMPILE_ERROR"
            result["reason"] = error.stderr if isinstance(error, subprocess.CalledProcessError) else str(error)
            draft = ROOT / "build/hand_wip/lib" / source.name
            draft.parent.mkdir(parents=True, exist_ok=True)
            source.replace(draft)
        results.append(result)
        save_json(ROOT / "build/reports/lib_matches.json", {"counts": dict(Counter(r["status"] for r in results)), "functions": results})
    (ROOT / "build/reports/lib_symbols.txt").write_text("".join(aliases), encoding="utf-8")
    save_json(ROOT / "build/reports/lib_matches.json", {"counts": dict(Counter(r["status"] for r in results)), "functions": results})
    print(dict(Counter(r["status"] for r in results)))


if __name__ == "__main__":
    main()

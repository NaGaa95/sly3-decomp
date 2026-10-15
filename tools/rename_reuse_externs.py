"""Replace stale reference address labels using decoded Sly 3 call operands."""
import argparse
import json
import re
from common import ROOT, save_json
from compiler import compile_source
from matchtool import object_functions, compare, functions
from object_evidence import function_evidence


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("report")
    args = parser.parse_args()
    path = ROOT / args.report
    report = json.loads(path.read_text())
    known = functions()
    changed = 0
    proposals = {}
    for function in report["functions"]:
        if function["status"] not in ("EXACT_MATCH", "NORMALIZED_MATCH"):
            continue
        for record in function.get("relocation_evidence", []):
            if record["type"] == 4 and record.get("expected_address") and record["symbol"]:
                proposals.setdefault(record["symbol"], set()).add(int(record["expected_address"], 16))
    for function in report["functions"]:
        if not function.get("source"):
            continue
        replacements = {}
        for record in function.get("relocation_evidence", []):
            if record["type"] != 4 or not record.get("expected_address"):
                continue
            symbol, address = record["symbol"], int(record["expected_address"], 16)
            canonical = re.fullmatch(r"func_([0-9A-Fa-f]{8})", symbol)
            known_address = known.get(symbol, (None, None))[0]
            if (canonical and int(canonical[1], 16) != address) or len(proposals.get(symbol, ())) > 1 or (known_address is not None and known_address != address):
                replacement = f"func_{address:08X}"
                if symbol in replacements and replacements[symbol] != replacement:
                    raise ValueError(f"One function references {symbol} at different addresses: {function['name']}")
                replacements[symbol] = replacement
        if not replacements:
            continue
        source = ROOT / function["source"]
        text = source.read_text(encoding="utf-8")
        for old, new in replacements.items():
            text = re.sub(r"\b" + re.escape(old) + r"\b", new, text)
        source.write_text(text, encoding="utf-8")
        output = ROOT / function["object"]
        compile_source(source, output)
        symbol = function.get("object_symbol", function["name"])
        local_known = dict(known)
        local_known[symbol] = known[function["name"]]
        result = compare(symbol, *object_functions(output)[symbol], known=local_known)
        if result["status"] not in ("EXACT_MATCH", "NORMALIZED_MATCH"):
            raise ValueError("Renamed source changed instruction shape: " + function["name"])
        function["relocation_evidence"] = function_evidence(output, symbol, int(function["address"], 16))
        function["extern_replacements"] = replacements
        changed += 1
    save_json(path, report)
    print(f"Corrected reference address labels in {changed} sources")


if __name__ == "__main__":
    main()

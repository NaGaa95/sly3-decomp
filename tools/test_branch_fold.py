"""Verify complete memcmp bytes and the branch-around-jump equivalence guard."""
from common import ROOT, save_json
from compiler import compile_source
from matchtool import compare_object, functions
from relocate import ObjectLinker, symbol_addresses
from asfix_branch_fold import fix


def main():
    source = ROOT / "src/lib/string/memcmp.c"
    output = compile_source(source, ROOT / "build/tests/memcmp.o")
    known, addresses = functions(), symbol_addresses()
    known["memcmp"] = known["func_00291DF8"]
    addresses["memcmp"] = 0x00291DF8
    result = compare_object("memcmp", output, known=known, linker=ObjectLinker(output, addresses=addresses))
    assert result["status"] == "EXACT_MATCH" and result["instructions"] == 37, result
    raw = output.with_suffix(".raw.s").read_text()
    _, policy = fix(raw)
    assert len(policy["folded_branches"]) == 1
    record = policy["folded_branches"][0]
    skip, exit_label = record["skip_label"], record["exit_label"]
    anchor = "\tbeq\t$9,$0," + skip
    assert anchor in raw and "\tmovz\t$5,$2,$9" in raw
    cases = {
        "branch-likely conditional": raw.replace(anchor, "\tbeql\t$9,$0," + skip),
        "condition register changed by delay": raw.replace("\tmovz\t$5,$2,$9", "\tmovz\t$9,$2,$9"),
        "memory operation moved before branch": raw.replace("\tmovz\t$5,$2,$9", "\tlw $5,0($2)"),
        "expanded first delay": raw.replace("\tmovz\t$5,$2,$9", "\tli $5,0x12345678"),
        "expanded jump delay": raw.replace("\taddu\t$4,$4,-16", "\tli $4,0x12345678"),
        "invalid GPR": raw.replace("\tmovz\t$5,$2,$9", "\tmovz $32,$2,$9"),
        "external jump target": raw.replace("\tb\t" + exit_label, "\tb\tExternal"),
        "unknown directive in span": raw.replace(skip + ":", "\t.org 0\n" + skip + ":"),
        "too large displacement": raw.replace(skip + ":", "\tnop\n" * 2000 + skip + ":"),
        "extra operation before skipped label": raw.replace(skip + ":", "\tmove $5,$2\n" + skip + ":"),
        "alternate entry before skipped label": raw.replace(skip + ":", "$Lextra:\n" + skip + ":"),
        "inline assembly containing branch": raw.replace(anchor, "#APP\n" + anchor).replace(skip + ":", "#NO_APP\n" + skip + ":"),
        "preceding bare control": raw.replace("\t.set\tnoreorder\n\t.set\tnomacro\n" + anchor,
                                              "\tbeq $11,$0," + exit_label + "\n\t.set\tnoreorder\n\t.set\tnomacro\n" + anchor),
    }
    refused = []
    for label, candidate in cases.items():
        assert not fix(candidate)[1]["folded_branches"], label
        refused.append(label)
    malformed = {
        "missing compiler marker": raw.replace("gcc2_compiled.:", ""),
        "nested mode": raw.replace("\t.set\tnomacro", "\t.set noreorder\n\t.set nomacro", 1),
        "unclosed function": raw.replace("\t.end\tmemcmp", ""),
        "unclosed inline block": raw + "#APP\n",
        "duplicate label": raw.replace(skip + ":", skip + ":\n" + skip + ":"),
    }
    for label, candidate in malformed.items():
        try:
            fix(candidate)
        except ValueError:
            refused.append(label)
        else:
            raise AssertionError("Malformed compiler input accepted: " + label)
    save_json(ROOT / "build/reports/branch_fold_validation.json", {
        "name": "memcmp", "status": result["status"], "bytes": 148,
        "policy": policy, "refused_cases": refused})
    print(f"PASS: exact 148-byte memcmp; {len(refused)} unsafe/malformed folds refused")


if __name__ == "__main__":
    main()

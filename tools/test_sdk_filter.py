"""Validate the SDK adaptation and refuse instruction moves changing behavior."""
from common import ROOT, save_json
from compiler import compile_source
from matchtool import compare, object_functions
from asfix_sdk import move_loop_delays


def main():
    output = compile_source(ROOT / "src/lib/memclr.c", ROOT / "build/tests/memclr.o")
    result = compare("memclr", *object_functions(output)["memclr"], known={"memclr": (0x29fa00, 56)})
    assert result["status"] == "EXACT_MATCH"
    cases = {
        "aliased-condition-register": ".set noreorder\nL:\n\tandi $2,$2,1\n\tbne $2,$0,L\n\tmove $v0,$a0\n",
        "expanded-immediate-macro": ".set noreorder\nL:\n\tlw $2,0($4)\n\tbne $2,$0,L\n\taddu $4,$4,65536\n",
        "branch-likely-untaken-path": ".set noreorder\nL:\n\tandi $2,$2,1\n\tbnel $2,$0,L\n\taddiu $4,$4,1\n",
        "memory-delay-side-effect": ".set noreorder\nL:\n\tandi $2,$2,1\n\tbne $2,$0,L\n\tsw $2,0($4)\n",
    }
    rejected = []
    for name, assembly in cases.items():
        try:
            move_loop_delays(assembly)
        except ValueError:
            rejected.append(name)
        else:
            raise AssertionError("Unsafe SDK rewrite admitted: " + name)
    save_json(ROOT / "build/reports/sdk_filter_validation.json", {"memclr": "EXACT_MATCH", "instructions": result["instructions"], "rejected_cases": rejected})
    print("PASS: memclr exact; aliased condition, expanded macro, likely branch and memory-side-effect moves refused")


if __name__ == "__main__":
    main()

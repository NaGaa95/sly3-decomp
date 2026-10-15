"""Compile sources and count only exact code after all relocations are resolved."""
import csv
import hashlib
import subprocess
import os
from concurrent.futures import ThreadPoolExecutor
from common import ROOT, Elf32, target_config, save_json
from compiler import compile_source
from matchtool import object_functions, compare, compare_object, functions
from relocate import ObjectLinker, RelocationError, symbol_addresses
from data_progress import object_data, summarize as summarize_data
from object_bindings import source_bindings


def collect():
    known = functions()
    addresses = symbol_addresses()
    addresses.update({name: value[0] for name, value in known.items() if name not in addresses})
    elf = Elf32((ROOT / "disc" / target_config()["serial"]).read_bytes())
    verified, pending, failures = {}, [], []
    patches = []
    data_matches, unresolved_data = [], []
    sources = [source for source in sorted((ROOT / "src").rglob("*")) if source.suffix in (".c", ".cpp", ".cc")]
    def compile_one(source):
        try:
            return compile_source(source, ROOT / "build/obj" / source.relative_to(ROOT / "src").with_suffix(".o")), None
        except (subprocess.CalledProcessError, subprocess.TimeoutExpired, ValueError) as error:
            return None, error
    workers = max(1, min(8, int(os.environ.get("SLY3_JOBS", "4"))))
    pool = ThreadPoolExecutor(max_workers=workers)
    compiled_sources = pool.map(compile_one, sources)
    for index, (source, (output, compile_error)) in enumerate(zip(sources, compiled_sources)):
        if source.suffix not in (".c", ".cpp", ".cc"):
            continue
        relative = source.relative_to(ROOT).as_posix()
        try:
            if compile_error:
                raise compile_error
            local_known, local_addresses = source_bindings(source, output, known, addresses)
            linker = ObjectLinker(output, target=elf, addresses=local_addresses)
            object_matches, object_unresolved = object_data(linker, source)
            data_matches.extend(object_matches)
            unresolved_data.extend(object_unresolved)
            if object_unresolved:
                raise RelocationError('Unverified emitted initialized data: ' +
                                      '; '.join(item['name'] + ': ' + item['reason']
                                                for item in object_unresolved))
            for name, (code, rel) in object_functions(output).items():
                if name.startswith("__tf"):
                    continue  # Generated RTTI is not counted as recovered game code.
                result = compare_object(name, output, elf, local_known, linker)
                if result["status"] in ("EXACT_MATCH", "LINKED_MATCH"):
                    address = result["address"]
                    if address in verified:
                        failures.append(f"Duplicate source for address {address:08X}")
                        continue
                    raw, _ = linker.function(name)
                    digest = hashlib.sha256(raw).hexdigest()
                    verified[address] = {"name": name, "address": f"0x{address:08X}", "instructions": result["instructions"], "status": result["status"], "source": relative}
                    patches.append({"address": address, "data": raw, "name": name, "source": relative, "sha256": digest, "relocations": result["relocation_evidence"], "constant_sections": result["constant_sections"]})
                elif result["status"] == "UNRESOLVED_RELOCATION":
                    shape = compare(name, code, rel, elf, local_known)
                    pending.append({"name": name, "source": relative, "reason": result["reason"], "shape_status": shape["status"]})
                    if shape["status"] == "DIFFERENT":
                        failures.append(f"{relative}: {name}: DIFFERENT")
                else:
                    failures.append(f"{relative}: {name}: {result['status']}")
        except (subprocess.CalledProcessError, subprocess.TimeoutExpired, RelocationError, ValueError) as error:
            reason = error.stderr if isinstance(error, subprocess.CalledProcessError) else str(error)
            failures.append(f"{relative}: {reason}")
        if (index + 1) % 100 == 0:
            print(f"Audited {index + 1}/{len(sources)} source files; {len(verified)} functions verified", flush=True)
    pool.shutdown(wait=True)
    with (ROOT / "config/matched.csv").open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=("name", "address", "instructions", "status", "source"))
        writer.writeheader()
        writer.writerows(verified[a] for a in sorted(verified))
    exact = sum(row["status"] == "EXACT_MATCH" for row in verified.values())
    linked = len(verified) - exact
    byte_count = sum(len(patch["data"]) for patch in patches)
    report = {"exact_functions": exact, "linked_functions": linked, "verified_functions": len(verified), "compiled_code_bytes": byte_count, "main_text_bytes": target_config()["text"]["size"], "main_text_percent": byte_count * 100 / target_config()["text"]["size"], "function_candidates": len({a for a, _ in known.values()}), "pending_relocations": pending, "failures": failures, "full_cpp_relink_complete": False}
    data_report = summarize_data(data_matches, unresolved_data)
    report['compiled_data_bytes'] = data_report['compiled_data_bytes']
    report['verified_data_objects_or_sections'] = data_report['verified_objects_or_sections']
    save_json(ROOT / "build/reports/progress.json", report)
    save_json(ROOT / "build/reports/source_patches.json", [{k: v for k, v in patch.items() if k != "data"} for patch in patches])
    print(f"Verified sources: {exact} exact leaves, {linked} fully relocated functions; {byte_count:,} bytes ({report['main_text_percent']:.2f}% of main EE text)")
    print(f"Pending: {len(pending)} relocation mappings; failures: {len(failures)}")
    print(f"Verified initialized data: {data_report['compiled_data_bytes']:,} unique bytes; {len(unresolved_data)} objects remain unresolved")
    for failure in failures[:10]:
        print(failure)
    return patches, report


def main():
    _, report = collect()
    raise SystemExit(1 if report["failures"] else 0)


if __name__ == "__main__":
    main()

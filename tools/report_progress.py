"""Write a readable checkpoint from a completed, internally consistent source build."""
import csv
import json
from collections import Counter
from datetime import datetime, timezone
from common import ROOT


def main():
    progress = json.loads((ROOT / 'build/reports/progress.json').read_text())
    build = json.loads((ROOT / 'build/reports/source_build.json').read_text())
    if not build['match'] or progress['failures']:
        raise ValueError('A successful source build is required for a checkpoint')
    for field in ('verified_functions', 'compiled_code_bytes', 'compiled_data_bytes'):
        if progress[field] != build[field]:
            raise ValueError('Progress and completed source build disagree: ' + field)
    groups = Counter()
    for row in csv.DictReader((ROOT / 'config/matched.csv').open()):
        groups[row['source'].split('/')[1]] += 1
    rows = '\n'.join('| `src/' + group + '` | ' + str(count) + ' |' for group, count in sorted(groups.items()))
    timestamp = datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M UTC')
    iop_text = 'The separate IOP source build has not yet been verified.'
    from iop_sources import current_components, current_modules, summarize
    iop = current_components()
    if iop:
        totals = summarize(iop)
        libraries = ', '.join('`'+item['module']+'`' for item in current_modules(iop))
        iop_text = f'''The separate IOP builds verify {totals['verified_source_functions']}
ordinary C functions / {totals['verified_source_code_bytes']} complete
code bytes and {totals['verified_source_initialized_data_bytes']} initialized data
bytes across {totals['unique_original_module_count']} unique original modules ({libraries}), with all source
relocations resolved. All native object groups are checked in full under both measured
scalar profiles, and disjoint whole function claims are merged once per original module. Each
combined partial IRX equals its original file. Their remaining
code and all import/export, relocation, header and BSS metadata are original
preservation inputs. Historical IOP compiler identity and the general original
O32 ABI remain unconfirmed. These counts are separate from main EE coverage;
`build/reports/component_inventory.json` records both components.'''
    from vu_union_sources import summarize as vu_summary
    vu = vu_summary()
    vu_text = f'''The separate readable VSM/VIF source build verifies
{vu['verified_source_functions']} known original VU routines / {vu['verified_source_code_bytes']}
native instruction bytes ({vu['VU_code_percent']:.2f}% of the {vu['original_unique_program_code_bytes']}
unique original VU code bytes across nine programs), in {vu['verified_source_programs']}
complete source programs. Two mesh programs, the volume, particle and silhouette programs have unknown original routine counts;
their 37, 30, 22, 3 and 10 authored source partitions and entry aliases add no function count.
The source build verifies {vu['DMA_protocol_bytes']} DMA and {vu['VIF_protocol_bytes']}
VIF control bytes separately. All {vu['verified_whole_runtime_upload_bytes']} bytes
of the {vu['verified_source_programs']} source-derived native runtime chains are consumed into
`build/vu/combined/SCUS_974.64.vu-union-source.elf`; this partial ELF is byte-identical
to the USA original. The retained renderer source and proof remain independently
verified. {vu['actual_resolved_nonallocated_metadata_relocations']} real nonallocated DVP metadata relocations are resolved;
generated/original zero overlay shadows,
debug file/line metadata, and CPU-provided input data add no source counts.
Whole native allocated data and BSS are empty. Historical VCL/compiler identity
and original debug metadata relinking remain unconfirmed. These VU counts are
separate from EE C/C++ coverage. `source_build.json` preserved-other-byte fields
remain EE-only accounting; the {vu['verified_source_code_bytes']} instruction
bytes and {vu['verified_source_protocol_bytes']} DMA/VIF control bytes each count
once, with no extra count for their whole runtime-chain bytes. The shipped VU0
radial entry1C0 has no identified direct EE caller; its architectural input
register reads and native flags/branches are preserved, and any dynamic launch
remains explicitly unconfirmed.'''
    content = f'''# Sly 3 decompilation checkpoint

Generated from the completed source build at {timestamp}. Later machine-readable
reports under `build/reports` and `config/matched.csv` are the current authority.

This checkpoint verifies
{progress['verified_functions']:,} C/C++ functions, comprising
{progress['compiled_code_bytes']:,} bytes ({progress['main_text_percent']:.2f}% of
the main EE executable text), and {progress['compiled_data_bytes']:,} unique
initialized data bytes. There are {len(progress['pending_relocations'])} pending
code relocations and {len(progress['failures'])} source failures in this build.

{iop_text}

{vu_text}

| Source group | Verified functions |
| --- | ---: |
{rows}

{progress['exact_functions']:,} functions match their raw compiled bytes;
{progress['linked_functions']:,} match after all actual object relocations are
resolved. Diagnostic masked comparisons, assembly preservation and unmatched
drafts contribute no completion count.

## Compiler and recovered components

GCC 2.95.3-136 with the SN EE assembler reproduces the verified engine cohorts.
Complete stream, heap, DMA, GIF and VIF files use `-Os -G0 -ffast-math
-mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti`. Other verified engine functions
use the documented `-O2` profile or explicit source-local settings. Original
zero RTTI entries distinguish `-fno-rtti`: seven complete virtual tables match
all 272 bytes after relocation. These profiles are established for tested code;
they do not identify one original command line for the entire executable.

Recovered components include stream decompression and readers, allocation and
dynamic-array methods, DMA/GIF/VIF packet builders, list/callback handling,
aligned memory-stack operations, `CopyAb`, script bindings, kernel wrappers,
scalar/record algorithms and runtime/library code. `memcpy`, `memmove` and
`memset`, `memcmp`, `strncmp`, `qsort` and the reentrant `strtol` parser match
their complete original functions. See [COMPILER.md](COMPILER.md)
for discriminating tests and explicit SDK adaptations.

## Build evidence and remaining scope

The output is `build/SCUS_974.64.source.elf`. Its SHA-256 is
`{build['sha256']}`, identical to the original USA `SCUS_974.64`.
This is a partial source build: {build['preserved_main_text_bytes']:,} main text
bytes and {build['preserved_other_bytes']:,} other file bytes remain original
preservation inputs. The checksum verifies all recovered replacements in their
original layout; it does not demonstrate complete recovery or full relinking.

{progress['verified_functions']:,} of {progress['function_candidates']:,} main EE functions are verified.
Not rebuilt from source: the remaining initialized globals, the
translation-unit/linker layout and most of the nine extracted IOP modules.
The intact `SLY3.WAD` is extracted from the supplied
disc; its encrypted PS2 catalog has not been converted into named assets.

The local portable compilers, Python libraries and Ghidra environment are ready
for building and checking the sources. No additional system installation is needed
for the work verified here. A complete game relink and other compiler cohorts
still need their own validation.

Run `.\\sly3.ps1 build`, `.\\sly3.ps1 selftest` and
`.\\sly3.ps1 verify` from the project directory. Regenerate this checkpoint
with `.\\.venv\\Scripts\\python.exe tools\\report_progress.py` after a completed
build. Detailed code/data evidence is in `build/reports/source_patches.json`,
`source_data_patches.json`, `source_build.json` and `data_progress.json`.
Use `.\\sly3.ps1 build-all` to build every currently admitted EE/IOP/VU source
component and update both inventories. `.\\sly3.ps1 iop-selftest` checks native
IOP output separately. The libsd and no-split cohorts have explicit
`iop-libsd-selftest` and `iop-nosplit-selftest` commands;
`.\\.venv\\Scripts\\python.exe tools\\test_iop_sources.py` checks merged module
ownership and freshness.
`.\\.venv\\Scripts\\python.exe tools\\test_vu_sources.py` checks full VU native
sections, relocation/domain ownership and source/tool/report freshness.
`.\\.venv\\Scripts\\python.exe tools\\test_vu_union.py` checks the complete
complete-program source union, exact dependency fingerprints and disjoint code/DMA/VIF
ownership without replacing the retained renderer proof.
'''
    destination = ROOT / 'docs/DECOMPILATION_REPORT.md'
    destination.write_text(content, encoding='utf-8')
    print(destination)


if __name__ == '__main__':
    main()

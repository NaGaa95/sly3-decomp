# Sly 3 decomp: work assignments

Target: `SCUS_974.64` (USA), SHA-1 `5941b7877e6bf5dfb8acb2d04a3c5059367f385b`. Only byte-identical, relocation-checked
(`LINKED_MATCH` / `EXACT_MATCH`) sources count, as in the Sly 2 project.

This fork (`Komasia/sly3-decomp`) tracks NaGa's repo (`NaGaa95/sly3-decomp`). Work happens here until access to the
upstream is sorted out; then the two are merged.

## Where the project stands (snapshot of NaGa's repo, 2026-10-30)

| | Done | Left |
|---|---|---|
| Functions | 6,828 of 8,551 (79.8%) | 1,723 |
| Code size | 871,508 of 1,825,712 bytes (47.7%) | 954,204 bytes |

Most of the small functions are done; the remaining work is concentrated in larger functions (median 92
instructions, 46 over 500 instructions, 10 over 1,000). NaGa's pipeline already builds and links matched sources
with full relocation checks, has VU and IOP builds, and reuses Sly 2 code through `tools/reference_sly2.py`.

## Ranges

The remaining code is split three ways by **bytes left**, in contiguous address ranges:

| Owner | Range | Functions left | Bytes left | Over 500 insns |
|---|---|---|---|---|
| **Dimitri + Claude agents** | `0x100000`–`0x1B0000` | 553 | 304,384 | 10 |
| **NaGa** | `0x1B0000`–`0x240000` | 468 | 324,348 | 18 |
| **Lilly** | `0x240000`–end (`0x2C0250`) | 702 | 325,472 | 18 |

Stay inside your own range. If you match something in someone else's range (for example while porting a whole Sly 2
source file), tell them before pushing so nobody duplicates work. Rebalance here when a range runs dry.

Biggest functions left in each range:
- Dimitri: `func_0018FF98` (2,694 insns), `func_001ADDD0` (1,236), `func_00150AE8` (952), `func_0018E800` (942)
- NaGa: `func_00226D00` (2,510), `func_001BBCA8` (1,236), `func_001B30E8` (1,026), `func_00229438` (1,022)
- Lilly: `func_002AC010` (1,898), `func_0028CA78` (1,804), `func_00274AC0` (1,684), `func_002B1038` (924)

## First step for everyone: re-run the Sly 2 reuse pass

`config/reference.json` points at Sly 2 revision `a4d782b`, from before Sly 2 was finished. Sly 2 is now 100%
matched and relocation-checked (6,662/6,662), and 16 address/constant mistakes were fixed in the last commit
(`e0aacd4`). Pointing `reference_sly2.py` / `find_reuse.py` at the current Sly 2 should turn up a batch of easy
matches across all three ranges, since Sly 3 runs on the same engine.

## Rules (carried over from Sly 2)
- Only byte-identical matches go into `src/`; relocations must resolve to the right symbols (the pipeline checks this).
- Never commit game data (ELF, ISO, disassembly) or compiler binaries.
- At most one commented register pin per function; no instruction asm that replaces plain C (VU helper inlines are fine);
  no invented global names (address-based `D_`/`func_` names are fine).
- Pull before you push; keep commits to your own range.

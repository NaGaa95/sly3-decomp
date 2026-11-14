# Credits

Sly 3: Honor Among Thieves (`SCUS_974.64`, NTSC-U) was fully matched on **2026-11-14**: all 8,723 functions of the
game executable compile to code that is byte-identical to the original, with every call and data reference pointing
at the right target.

## Who did what

Counted by who first committed each matched source file (`config/credits.csv`).

| Who | Functions matched | Instructions | Main areas |
|---|---|---|---|
| **NaGa** (NaGaa95) | 7,344 | 302,997 | Project setup and build pipeline (relocation-checked EE build, VU and IOP builds, reuse of Sly 2 code), the first 6,828 functions across the whole executable, then 0x1B0000–0x240000 and the last functions |
| **Dimitri** (Komasia) | 1,379 | 153,328 | 0x100000–0x1B0000 and 0x240000–end, the Sony SDK library compilers and GNU-as path, README and progress graph |

## Timeline
- **2026-10-15** — NaGa publishes the repo with the build pipeline, the nine VU programs and the first 4,796
  matched functions.
- **2026-10-19** — 6,828 of the 8,551 functions known at that point are matched (47.7% of the code).
- **2026-10-30** — Dimitri joins. The remaining work is split by address: 0x100000–0x1B0000 for Dimitri,
  0x1B0000–0x240000 for NaGa.
- **2026-11-06** — Dimitri also takes 0x240000–end.
- **2026-11-14** — last functions matched (8,723 / 8,723, after boundary corrections to the function list).

## Tools and references
- [decomp.me compilers](https://github.com/decompme/compilers) (ee-gcc builds, SN `ps2eeas`)
- [wibo](https://github.com/decompals/wibo), [m2c](https://github.com/matt-kempster/m2c),
  [rabbitizer / spimdisasm / splat](https://github.com/Decompollaborate)
- [Ghidra](https://github.com/NationalSecurityAgency/ghidra) with
  [ghidra-emotionengine-reloaded](https://github.com/chaoticgd/ghidra-emotionengine-reloaded),
  [SlyTools](https://github.com/VelocityRa/SlyTools)
- The [Sly 2 decompilation](https://github.com/Komasia/sly2-decomp), used as a reference for the shared engine code
  and the Sony SDK libraries
- [PS2SDK](https://github.com/ps2dev/ps2sdk), used as a reference for the IOP modules (`iop/licenses/PS2SDK.MIT`)

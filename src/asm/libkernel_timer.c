/* Sony's original hand-written assembly (no C equivalent exists):
 * libkernel iGetTimerSystemTime.
 * Evidence: it reads the T0 timer registers directly (lwu from 0x10001000) with 64-bit ld/dsll/dsllv
 * arithmetic on raw t-registers and no stack frame, which ee-gcc never produces from C.
 * Sly 2 counterpart: src/lib/iGetTimerSystemTime.c (0x0023A1D0); only its data address
 * differs (D_0034B650).
 * The finished Sly 2 decomp keeps it as the same kind of top-level asm block.
 * Each routine is a top-level __asm__ block under .set noreorder, so the assembler emits it exactly as written;
 * the global symbols are the Sly 3 address names (the original names are in the per-block comments). */

/* func_00298E50 = Sly 2 iGetTimerSystemTime */
__asm__(
    ".set noreorder\n"
    ".text\n"
    ".globl func_00298E50\n"
    ".ent func_00298E50\n"
    "func_00298E50:\n"
    "lui $3, 0x1000\n"
    "lui $4, %hi(D_0034B650)\n"
    "ori $3, $3, 0x1000\n"
    "lwu $2, 0($3)\n"
    "lw $8, 0x10($3)\n"
    "ld $10, %lo(D_0034B650)($4)\n"
    "andi $9, $8, 0x800\n"
    "beqz $9, 1f\n"
    "addiu $9, $0, 2\n"
    "lwu $2, 0($3)\n"
    "daddiu $10, $10, 1\n"
    "1:\n"
    "andi $8, $8, 3\n"
    "dsll $10, $10, 16\n"
    "movz $9, $0, $8\n"
    "or $2, $2, $10\n"
    "dsllv $9, $9, $8\n"
    "dsllv $2, $2, $9\n"
    "jr $31\n"
    "nop\n"
    ".end func_00298E50\n"
    ".set reorder\n"
);

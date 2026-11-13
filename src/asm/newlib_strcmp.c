/* Sony's original hand-written assembly (no C equivalent exists):
 * newlib's r5900 strcmp (libc string routine, like memcmp/memcpy).
 * Evidence: it compares 16 bytes per step with 128-bit lq and MMI psubw/pnor/psubb/pand/pcpyud
 * (TI-mode operations ee-gcc cannot generate from C), builds its 64-bit masks with the assembler's
 * dli expansion, and reuses registers the way an asm programmer does (pcpyud's don't-care rt $a0).
 * Sly 2 counterpart: src/lib/func_002401D8.c (0x002401D8), identical instructions.
 * The finished Sly 2 decomp keeps it as the same kind of top-level asm block.
 * Each routine is a top-level __asm__ block under .set noreorder, so the assembler emits it exactly as written;
 * the global symbols are the Sly 3 address names (the original names are in the per-block comments). */

/* func_0029EE58 = Sly 2 func_002401D8 */
__asm__(
    ".set noreorder\n"
    ".set noat\n"
    ".text\n"
    ".globl func_0029EE58\n"
    ".ent func_0029EE58\n"
    "func_0029EE58:\n"
    "or $t0, $a0, $a1\n"
    "andi $v0, $t0, 0x7\n"
    "bnel $v0, $zero, L29EF90\n"            /* not 8-aligned: bytewise */
    "lb $v0, 0x0($a0)\n"
    "andi $t1, $t0, 0xF\n"
    /* $a3 = 0x0101010101010101 */
    "ori $a3, $zero, 0x8080\n"
    "dsll $a3, $a3, 16\n"
    "ori $a3, $a3, 0x8080\n"
    "dsll $a3, $a3, 16\n"
    "ori $a3, $a3, 0x8080\n"
    "dsll $a3, $a3, 9\n"
    "ori $a3, $a3, 0x101\n"
    /* $a2 = 0x8080808080808080 */
    "ori $a2, $zero, 0x8080\n"
    "dsll $a2, $a2, 16\n"
    "ori $a2, $a2, 0x8080\n"
    "dsll $a2, $a2, 16\n"
    "ori $a2, $a2, 0x8080\n"
    "dsll $a2, $a2, 16\n"
    "ori $a2, $a2, 0x8080\n"
    "bnez $t1, L29EF24\n"                   /* 8- but not 16-aligned */
    "ld $v0, 0x0($a1)\n"
    /* 16 bytes at a time */
    "lq $v1, 0x0($a0)\n"
    "pcpyld $t0, $a3, $a3\n"
    "lq $v0, 0x0($a1)\n"
    "pcpyld $t2, $a2, $a2\n"
    "psubw $a3, $v0, $v1\n"
    "pcpyud $a2, $a3, $a0\n"
    "or $v1, $a2, $a3\n"
    "bnel $v1, $zero, L29EF90\n"            /* first qwords differ */
    "lb $v0, 0x0($a0)\n"
    "lq $v0, 0x0($a0)\n"
    "pnor $v1, $zero, $v0\n"
    "L29EED8:\n"
    "psubb $v0, $v0, $t0\n"
    "pand $v0, $v0, $v1\n"
    "pand $v0, $v0, $t2\n"
    "pcpyud $v1, $v0, $a0\n"
    "or $a2, $v1, $v0\n"
    "beqz $a2, L29EEFC\n"
    "addiu $a0, $a0, 0x10\n"
    "jr $ra\n"                              /* equal and contains the NUL */
    "daddu $v0, $zero, $zero\n"
    "L29EEFC:\n"
    "addiu $a1, $a1, 0x10\n"
    "lq $v0, 0x0($a0)\n"
    "lq $v1, 0x0($a1)\n"
    "psubw $a3, $v0, $v1\n"
    "pcpyud $a2, $a3, $a0\n"
    "or $t1, $a2, $a3\n"
    "beql $t1, $zero, L29EED8\n"
    "pnor $v1, $zero, $v0\n"
    "b L29EF90\n"
    "lb $v0, 0x0($a0)\n"
    /* 8 bytes at a time */
    "L29EF24:\n"
    "ld $v1, 0x0($a0)\n"
    "bnel $v1, $v0, L29EF90\n"
    "lb $v0, 0x0($a0)\n"
    "ld $v0, 0x0($a0)\n"
    "nor $t0, $zero, $v0\n"
    "L29EF38:\n"
    "dsubu $v0, $v0, $a3\n"
    "and $v0, $v0, $t0\n"
    "and $v0, $v0, $a2\n"
    "beqz $v0, L29EF54\n"
    "addiu $a0, $a0, 0x8\n"
    "jr $ra\n"                              /* equal and contains the NUL */
    "daddu $v0, $zero, $zero\n"
    "L29EF54:\n"
    "addiu $a1, $a1, 0x8\n"
    "ld $v0, 0x0($a0)\n"
    "ld $v1, 0x0($a1)\n"
    "beql $v1, $v0, L29EF38\n"
    "nor $t0, $zero, $v0\n"
    "b L29EF90\n"
    "lb $v0, 0x0($a0)\n"
    /* bytewise; $v0 = *(signed char *)s1 on entry */
    "L29EF70:\n"
    "sll $v0, $v1, 24\n"
    "lb $v1, 0x0($a1)\n"
    "sra $v0, $v0, 24\n"
    "bnel $v0, $v1, L29EF98\n"
    "lbu $v1, 0x0($a0)\n"
    "addiu $a0, $a0, 0x1\n"
    "addiu $a1, $a1, 0x1\n"
    "lb $v0, 0x0($a0)\n"
    "L29EF90:\n"
    "bnez $v0, L29EF70\n"
    "lbu $v1, 0x0($a0)\n"
    "L29EF98:\n"
    "lbu $v0, 0x0($a1)\n"
    "jr $ra\n"
    "subu $v0, $v1, $v0\n"
    ".end func_0029EE58\n"
    ".set at\n"
    ".set reorder\n"
);

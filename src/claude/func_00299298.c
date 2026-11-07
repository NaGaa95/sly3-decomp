// Sly 2 counterpart: func_0023A618 (decomp src/lib/func_0023A618.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// 2/19 diffs: loop body `sw v1,0(v0)` / `addiu a0,-1` scheduled in the opposite order. (2.95.3: 10 diffs, $a1 copy)
typedef struct E { struct E *next; int a, b, c; } E;
extern E D_004CEC80[64];
extern E *D_004CF080;
int func_00299298(void)
{
    int i;
    D_004CF080 = D_004CEC80;
    for (i = 0; i < 64; i++) D_004CEC80[i].next = &D_004CEC80[i + 1];
    D_004CEC80[63].next = 0;
    return 0;
}

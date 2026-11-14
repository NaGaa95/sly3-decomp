// Sly 2 counterpart: func_0023A618 (decomp src/lib/func_0023A618.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
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

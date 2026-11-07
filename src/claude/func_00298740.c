// Sly 2 counterpart: func_00239AC0 (decomp src/lib/func_00239AC0.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
void SetT2(volatile int *addr, int val);
void func_00298740(int val)
{
    SetT2((volatile int *)0xB0001010, val);
}

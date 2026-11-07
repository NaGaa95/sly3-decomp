// Sly 2 counterpart: func_00239AD0 (decomp src/lib/func_00239AD0.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
void SetT2(volatile int *addr, int val);
void func_00298750(int val)
{
    SetT2((volatile int *)0xB0001020, val);
}

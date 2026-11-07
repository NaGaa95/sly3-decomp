// Sly 2 counterpart: setD4_CHCR (decomp src/lib/setD4_CHCR.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
int func_002980D0(void);
int func_00298120(void);
void func_002B3658(unsigned int v)
{
    int r = func_002980D0();
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | 0x10000;
    *(volatile unsigned int *)0x1000B400 = v;
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~0x10000;
    if (r) func_00298120();
}

// Sly 2 counterpart: func_00235110 (decomp src/lib/func_00235110.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
int func_002980D0(void);
int func_00298120(void);
int func_00293410(int);
int func_00293E60(int ch)
{
    int st;
    int r;
    __asm__ volatile("mfc0 %0, $12" : "=r"(st));
    st &= 0x10000;
    if (st) func_002980D0();
    r = func_00293410(ch);
    __asm__ volatile("sync");
    if (st) func_00298120();
    return r;
}

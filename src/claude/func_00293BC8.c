// Sly 2 counterpart: func_00234F48 (decomp src/lib/func_00234F48.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
void func_002980D0(void);
void func_00293B20(unsigned int, unsigned int);
void func_00298120(void);
void func_00293BC8(unsigned int start, unsigned int end)
{
    int s;
    __asm__ volatile("mfc0 %0, $12" : "=r"(s));
    s &= 0x10000;
    if (s) func_002980D0();
    func_00293B20(start & ~0x3F, end & ~0x3F);
    if (s) func_00298120();
}

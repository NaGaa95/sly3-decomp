// Sly 2 counterpart: flushByteBoundary (decomp src/lib/flushByteBoundary.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
void func_002B2EB8(void *d);
void func_002B2EF0(void *d, int n);
void func_002B3058(void *d)
{
    int n;
    func_002B2EB8(d);
    n = -(*(volatile unsigned int *)0x10002020 & 7) & 7;
    if (n) func_002B2EF0(d, n);
}

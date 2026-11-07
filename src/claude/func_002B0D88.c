// Sly 2 counterpart: _waitIpuIdle (decomp src/lib/_waitIpuIdle.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
void func_002B0890(void *mp);
void func_002B0D88(void *mp)
{
    if ((*(volatile unsigned int *)0x10002010 & 0x80004000) == 0x80000000)
        func_002B0890(mp);
}

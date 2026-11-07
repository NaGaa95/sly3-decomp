// Sly 2 counterpart: _sceMpegFlushBuf (decomp src/lib/_sceMpegFlushBuf.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p0[0x828]; int x828; unsigned int x82C; char p1[0x848 - 0x830]; int x848; int x84C; } D;
void func_002B0D88(D *d);
long func_002B09F8(D *d);
void func_002B0CF0(D *d, unsigned int n)
{
    func_002B0D88(d);
    n |= 0x40000000;
    *(volatile unsigned int *)0x10002000 = n;
    n &= 0xF0000000;
    d->x82C = n;
    if (n == 0x20000000 || n == 0x30000000 || n == 0x40000000)
        d->x828 = 0;
    else
        d->x828 = 1;
    d->x848 = func_002B09F8(d);
    d->x84C = 32;
}

// Sly 2 counterpart: _sceMpegNextBit (decomp src/lib/_sceMpegNextBit.c)
// (Claude agent) MATCH: r computed before the x84C=32 store.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p0[0x828]; int x828; unsigned int x82C; char p1[0x848 - 0x830]; unsigned int x848; int x84C; } D;
void func_002B0D88(D *d);
long func_002B09F8(D *d);
unsigned int func_002B0B78(D *d, int n)
{
    unsigned int r, c, m;
    func_002B0D88(d);
    if (d->x828 || d->x84C < n) {
        *(volatile unsigned int *)0x10002000 = 0x40000000;
        d->x828 = 0;
        d->x82C = 0x40000000;
        d->x848 = func_002B09F8(d);
    }
    r = d->x848 >> (32 - n);
    d->x84C = 32;
    c = n | 0x40000000;
    *(volatile unsigned int *)0x10002000 = c;
    m = c & 0xF0000000;
    d->x82C = m;
    if (m == 0x20000000 || m == 0x30000000 || m == 0x40000000)
        d->x828 = 0;
    else
        d->x828 = 1;
    d->x848 = func_002B09F8(d);
    return r;
}

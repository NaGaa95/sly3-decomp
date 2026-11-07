// Sly 2 counterpart: _sceMpegFlush (decomp src/lib/_sceMpegFlush.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    int x0; int x4; int x8; char p0[0xC0 - 0xC]; int xC0; char p0a[0x128 - 0xC4]; int x128; char p0b[0x130 - 0x12C]; int x130;
    char p2[0x184 - 0x134]; int x184;
    char p3[0x1C8 - 0x188]; void *a[4]; void *b[4]; void *c[4];
} D;
typedef struct { int x0, x4, x8; char p0[0x40 - 0xC]; D *sys; } sceMpeg;
void _sceMpegError(D *d, const char *msg);
void func_002AA6A8(D *d, void *img, int n);
void func_002AA968(D *d, void *i0, void *i1, int n);
int func_002AAD88(sceMpeg *mp)
{
    D *d = mp->sys;
    int r = 0;
    if (d->x4 && d->x8) {
        int n = d->x128;
        if (d->x130)
            _sceMpegError(d, "the second field is missing");
        else if (d->x184 == 3)
            func_002AA6A8(d, d->a[1], n - 1);
        else
            func_002AA968(d, d->b[1], d->c[1], n - 1);
        d->x130 = 0;
        mp->x8 = d->x128 - d->xC0;
        d->x4 = 0;
        r = 1;
    }
    return r;
}

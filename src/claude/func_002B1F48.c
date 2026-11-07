// Sly 2 counterpart: _sceMpegSliceA0 (decomp src/lib/_sceMpegSliceA0.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct {
    char p0[0x12C]; int err;
    char p130[0x13C - 0x130]; int mb_width;
    char p140[0x1C0 - 0x140]; int x1C0; int qscale;
    char p1C4[0x878 - 0x1C8]; int stop;
} D;
unsigned int func_002B0B78(D *d, int n);
unsigned int func_002B0C60(D *d, int n);
void func_002B2EF0(D *d, int n);
void func_002B3050(D *d);
void func_002B3058(D *d);
void _sceMpegError(D *d, const char *msg);
void func_002AE4B8(D *d, const char *fmt, unsigned int v);
int func_002B0718(D *d);
int func_002B1F48(D *d, void *unused, int *mbaddr, int *mbinc, int *pmv)
{
    unsigned int code;
    int inc;

    d->err = 0;
    func_002B3058(d);
    while (func_002B0C60(d, 24) != 1 && !d->stop)
        func_002B2EF0(d, 8);
    code = func_002B0C60(d, 32);
    if (code - 0x101 >= 0xAF) {
        func_002AE4B8(d, "slice_start_code(0x%08x) out of range", code);
        return 2;
    }
    func_002B3050(d);
    d->qscale = func_002B0B78(d, 5);
    if (func_002B0B78(d, 1)) {
        func_002B0B78(d, 1);
        func_002B2EF0(d, 7);
        while (func_002B0B78(d, 1))
            func_002B2EF0(d, 8);
    }
    inc = func_002B0718(d);
    *mbinc = inc;
    if (!d->err) {
        *mbaddr = ((code & 0xFF) - 1) * d->mb_width + inc - 1;
        *mbinc = 1;
        d->x1C0 = 1;
        pmv[5] = 0;
        pmv[4] = 0;
        pmv[1] = 0;
        pmv[0] = 0;
        pmv[7] = 0;
        pmv[6] = 0;
        pmv[3] = 0;
        pmv[2] = 0;
    return 0;
    }
    _sceMpegError(d, "_sceMpegSliceA0(): error happens");
    return 1;
}

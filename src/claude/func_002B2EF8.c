// Sly 2 counterpart: _sceMpegNextHeader (decomp src/lib/_sceMpegNextHeader.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int type; int pad; long pts; long dts; } CBTS;
typedef struct {
    char p0[0x160]; int picture_coding_type;
    char p164[0x838 - 0x164]; long pts; long dts;
    char p848[0x868 - 0x848]; void *mp;
    char p86C[0x878 - 0x86C]; int stop;
} D;
unsigned int func_002B0B78(D *d, int n);
unsigned int func_002B0C60(D *d, int n);
void func_002B2EF0(D *d, int n);
void func_002B3058(D *d);
void func_002B2400(D *d);
void func_002B26B0(D *d);
void func_002B2750(D *d);
int _sceMpegDispatchMpegCallback(void *mp, void *cb);
int func_002B2EF8(D *d)
{
    unsigned int code;
    CBTS cb;

    for (;;) {
        if (d->stop)
            return -1;
        func_002B3058(d);
        while (func_002B0C60(d, 24) != 1 && !d->stop)
            func_002B2EF0(d, 8);
        code = func_002B0B78(d, 32);
        switch (code) {
        case 0x1B3:
            func_002B2400(d);
            break;
        case 0x1B8:
            func_002B26B0(d);
            break;
        case 0x100:
            func_002B2750(d);
            cb.type = 5;
            cb.pts = -1;
            cb.dts = -1;
            _sceMpegDispatchMpegCallback(d->mp, &cb);
            d->pts = cb.pts;
            d->dts = cb.dts;
            return d->picture_coding_type;
        case 0x1B7:
            return 0;
        }
    }
}

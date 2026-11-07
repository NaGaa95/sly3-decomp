// Sly 2 counterpart: _sceMpegPictureData0 (decomp src/lib/_sceMpegPictureData0.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct {
    char p0[0x13C]; int mb_width; int mb_height;
    char p144[0x184 - 0x144]; int picture_structure;
    char p188[0x820 - 0x188]; int x820; int x824;
    char p828[0x848 - 0x828]; int x848; int x84C;
    char p850[0x868 - 0x850]; void *mp;
    char p86C[0x878 - 0x86C]; int stop;
} D;
#define R(a) (*(volatile unsigned int *)(a))
int func_002AF8C8(D *d, int n);
void func_002B0D88(D *d);
int func_002AA110(void *mp);
void _sceMpegStopIpuDma(void);
void func_002AE398(D *d);
void func_002AF468(D *d, int f);
void _sceMpegError(D *d, const char *msg);
extern const char D_0032C770[];

static inline int _waitBdec(D *d)
{
    int ok;

    ok = 1;
    func_002B0D88(d);
    func_002B0D88(d);
    if (R(0x1000B020) && !(R(0x10002010) & 0x4000)) {
        do {
            if (R(0x1000B420) == 0 && !(R(0x1000B400) & 0x100))
                func_002AA110(d->mp);
            if (d->stop) {
                _sceMpegStopIpuDma();
                return 0;
            }
            if (R(0x1000B020) == 0)
                break;
        } while (!(R(0x10002010) & 0x4000));
    }
    {
        unsigned int bp = R(0x10002020);
        long top = *(volatile long *)0x10002030;
        int bits;
        d->x848 = top;
        if (top < 0) {
            int k = bp & 0x1F;
            bits = k ? 32 - k : 0;
        } else
            bits = 32;
        d->x84C = bits;
    }
    if (R(0x10002010) & 0x4000) {
        func_002AE398(d);
        ok = 0;
    }
    return ok;
}

int func_002AF688(D *d)
{
    int n, r;

    d->x820 = 0;
    n = d->mb_width * d->mb_height;
    d->x824 = 0;
    if (d->picture_structure != 3)
        n >>= 1;
    do {
        r = func_002AF8C8(d, n);
    } while (r == 1 || r == 3);
    if (!_waitBdec(d)) {
        if (d->stop)
            return 4;
        r = 2;
    }
    {
        int st;
        do {
            st = (R(0x1000D400) >> 8) & 1;
            __asm__ volatile("nop\n\tnop");
        } while (st);
    }
    if (r == 0)
        func_002AF468(d, d->x820 == 0);
    if (r == 1 || r == 2)
        _sceMpegError(d, D_0032C770);
    return r == 0;
}

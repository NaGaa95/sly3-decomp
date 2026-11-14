// Sly 2 counterpart: _decodeOrSkipFrame (decomp src/lib/_decodeOrSkipFrame.c)
// Inline _decodeFrame: `t = 0` set after the func_002A98B8 call (v0 still live -> t in v1).
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int type; int pad[7]; } sceMpegCbData;
typedef int (*sceMpegCallback)(void *mp, sceMpegCbData *cbd, void *data);
typedef struct { sceMpegCallback func; void *data; void *gp; } CB;
typedef struct {
    int x0; int x4; int x8; char pC[0xC0 - 0xC]; int xC0;
    char pC4[0x128 - 0xC4]; int x128; char p12C[0x130 - 0x12C]; int second_field;
    char p134[0x184 - 0x134]; int picture_structure;
    char p188[0x878 - 0x188]; int stop;
} D;
typedef struct { int x0, x4, x8; char p0[0x40 - 0xC]; void *sys; } sceMpeg;
static inline void *SetGp(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $28\n\tmove $28, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
static inline int _sceMpegDispatchMpegCbNodata(sceMpeg *mp)
{
    sceMpegCbData cbd;
    CB *t;
    sceMpegCallback f;
    cbd.type = 1;
    if (mp && (t = ((CB **)mp)[16]) && (f = (t + cbd.type)[1].func)) {
        void *old = SetGp(((void **)(t + cbd.type))[5]);
        f(mp, &cbd, (t + cbd.type)[1].data);
        SetGp(old);
    }
    return 1;
}
int func_002A98B8(D *d, int second);
int func_002AA250(D *d);
void func_002AAE48(D *d, int a, int b);
static inline int _decodeFrame(D *d)
{
    int t, u = func_002A98B8(d, 0);
    t = 0;
    if (u) t = func_002AA250(d) != 0;
    return t;
}
int func_002A9B70(sceMpeg *mp, int n, int limit)
{
    D *d = mp->sys;
    int skipped = 0;
    int r;

    if (limit == -1 || n < limit) {
        if (d->x8 == 0) {
            mp->x8 = 0;
            d->x8 = 1;
        }
        r = _decodeFrame(d);
    } else {
        r = func_002A98B8(d, 0);
        _sceMpegDispatchMpegCbNodata(mp);
        skipped = 1;
    }
    if (d->stop)
        return 0;
    func_002AAE48(d, d->x128, d->x4);
    if (d->picture_structure != 3 && !skipped)
        d->second_field = !d->second_field;
    mp->x8 = d->x128 - d->xC0;
    if (!d->second_field) {
        d->x128++;
        d->x4++;
    }
    return r;
}

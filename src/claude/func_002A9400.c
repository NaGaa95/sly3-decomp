// Sly 2 counterpart: sceMpegCreate (decomp src/lib/sceMpegCreate.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY3_ASM: gnu-reorder-db
typedef struct {
    int width, height, frameCount;
    long pts, dts;
    unsigned long flags;
    long pts2nd, dts2nd;
    unsigned long flags2nd;
    void *sys;
} sceMpeg;
typedef struct { int (*func)(); void *data; void *gp; } CB;
#define CBS ((CB *)(d + 0xC))
#define W(o) (*(int *)((char *)d + (o)))
#define L(o) (*(long *)((char *)d + (o)))
#define P(o) (*(void **)((char *)d + (o)))
void *func_00292034(void *, int, int);
void _sceMpegError(void *, const char *, int);
void func_002AE4B8(void *, const char *, int);
void func_002AA320(void *, void *, int);
int func_002AA358(void *, void *, int, int);
void func_002A9330(void *);
void func_002A9FB8(sceMpeg *);
int func_002AA1D0(sceMpeg *);
void func_002AA338(void *);
int func_002AA3C8();
int func_002AA3F0();
extern char D_0032C4B8[], D_0032C468[], D_0032C490[];
int func_002A9400(sceMpeg *mp, unsigned char *work, int size)
{
    char *d;
    void *bs;
    int rem;
    int r;
    func_00292034(work, 0, size);
    d = (char *)((((unsigned int)work + 3) >> 2) << 2);
    rem = size - (d - (char *)work);
    if (rem < 0x19A0) {
        _sceMpegError(d, D_0032C4B8, rem);
        return 0;
    }
    bs = d + 0x118;
    mp->sys = d;
    func_002AA320(bs, d + 0x19A0, rem - 0x19A0);
    mp->width = 0;
    mp->height = 0;
    mp->frameCount = 0;
    mp->pts = -1;
    mp->dts = -1;
    mp->flags = 0;
    mp->pts2nd = -1;
    mp->dts2nd = -1;
    mp->flags2nd = 0;
    W(0xC8) = 0; W(0xCC) = 0; W(0xD0) = 0; W(0xD4) = 0;
    W(0xD8) = 0; W(0xDC) = 0; W(0xE0) = 0; W(0xE4) = 0;
    W(0xE8) = 0; W(0xEC) = 0; W(0xF0) = 0; W(0xF4) = 0;
    W(0xF8) = 0; W(0xFC) = 0; W(0x108) = 0;
    CBS[0].func = 0; CBS[1].func = 0; CBS[4].func = 0; CBS[5].func = 0; CBS[6].func = 0;
    L(0x100) = -1;
    CBS[2].func = func_002AA3C8;
    CBS[3].func = func_002AA3F0;
    r = func_002AA358(d, bs, 0x800, 8);
    W(0x64) = 0;
    W(0x10C) = 0; W(0x110) = 0; W(0x114) = 0;
    W(0x8C) = 0;
    L(0x90) = 0;
    W(0x98) = -1;
    L(0xA0) = 0;
    W(0x9C) = 0;
    W(0xC0) = 0;
    W(0xA8) = -1; W(0xAC) = -1; W(0xB0) = -1;
    P(0x868) = mp;
    W(0x60) = r;
    W(0xC4) = 1;
    func_002A9330(d);
    func_002A9FB8(mp);
    func_002AA1D0(mp);
    P(0x1C8) = d + 0x1F8;
    P(0x1CC) = d + 0x260;
    P(0x1D4) = d + 0x2C8;
    P(0x1D8) = d + 0x330;
    P(0x1DC) = d + 0x398;
    P(0x1E4) = d + 0x400;
    P(0x1E8) = d + 0x468;
    P(0x1EC) = d + 0x4D0;
    P(0x1F4) = d + 0x538;
    func_002AA338(bs);
    W(0x860) = -1;
    W(0x85C) = 0;
    W(0x864) = 0;
    if ((rem = (unsigned int)(d + 0x140) & 63)) {
        func_002AE4B8(d, D_0032C468, rem);
        return 0;
    }
    if ((unsigned int)(d + 0x880) & 63) {
        func_002AE4B8(d, D_0032C490, (unsigned int)(d + 0x880) & 63);
        return 0;
    }
    return 1;
}

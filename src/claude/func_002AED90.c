// Sly 2 counterpart: _motionComp0 (decomp src/lib/_motionComp0.c)
// libmpeg func_002AED90: intra-path pointer setup in do{}while(0) (loop-depth ref weighting fixes s-reg priority),
// non-intra pointers set before func_002AE688; first IPU wait is a goto loop (unpadded, address rematerialised).
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int x0; int p4[3]; int x10; } FRM;
typedef struct {
    char p0[0x12C]; int x12C;
    char p130[0x13C - 0x130]; int mb_width;
    char p140[0x184 - 0x140]; int picture_structure;
    char p188[0x1D0 - 0x188]; FRM *x1D0;
    char p1D4[0x1E0 - 0x1D4]; FRM *x1E0;
    char p1E4[0x1F0 - 0x1E4]; FRM *x1F0;
    char p1F4[0x6C8 - 0x1F4]; int x6C8; int x6CC; int x6D0; int x6D4; int x6D8;
    char p6DC[0x820 - 0x6DC]; int x820;
} D;
#define R(a) (*(volatile unsigned int *)(a))
#define MB(p) (*(int *)((char *)(p) + d->x820 * 0x140))
void func_002AE4B8(D *d, const char *msg, int v);
void func_002AE688(D *d, int x, int y, int mbtype, int mtype);
void func_002B1038(D *d);
extern const char D_0032C730[];

int func_002AED90(D *d, int addr, int fs, int mbtype, int mtype)
{
    int *p0, *p8, *pC, *p10;
    int intra = mbtype & 1;
    int y = addr / d->mb_width;
    int x = addr % d->mb_width;
    int x16 = x << 4;
    int y16 = y << 4;
    FRM *f;

    if (intra) {
        int i = d->x820;
        do { p10 = &d->x6D8; pC = &d->x6D4; p8 = &d->x6D0; p0 = &d->x6C8; } while (0);
    wait:
        if ((R(0x1000D400) >> 8) & 1) goto wait;
        *(int *)((char *)p10 + i * 0x140) = 0;
    } else {
        if (mtype - 1 >= 3u) {
            func_002AE4B8(d, D_0032C730, mtype);
            d->x12C = 1;
            return 0;
        }
        p10 = &d->x6D8; pC = &d->x6D4; p8 = &d->x6D0; p0 = &d->x6C8;
        func_002AE688(d, x16, y16, mbtype, mtype);
        while ((R(0x1000D400) >> 8) & 1) ;
        func_002B1038(d);
        MB(p10) = 1;
    }
    if (fs == 1 && (mbtype & 2))
        MB(pC) = fs;
    else
        MB(pC) = 0;
    MB(p8) = intra;
    if (d->picture_structure == 3) {
        MB(p0) = d->x1D0->x0 + (x * d->x1D0->x10 + y) * 0x180;
    } else {
        if (d->picture_structure == 2)
            f = d->x1F0;
        else
            f = d->x1E0;
        MB(p0) = f->x0 + (x * f->x10 + y) * 0x180;
    }
    return 1;
}

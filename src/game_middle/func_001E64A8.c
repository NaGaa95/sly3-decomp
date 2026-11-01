// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct X;
typedef struct { short d; short pad; M4 *(*pfn)(struct X *); } VT;
struct X { int x0, x4, x8; VT *vt; char pad[0xD8 - 0x10]; int c; char pad2[0xE4 - 0xDC]; qword *apos; };
int func_001E63B8(qword a, qword b);
int func_001E6428(qword a, qword b, qword c);
int func_001E66D8(struct X *p, int i);
static inline qword MulPt(M4 *m, qword v) { qword r; __asm__("vmulax.xyz ACC, %1, %2x\n\tvmadday.xyz ACC, %3, %2y\n\tvmaddaz.xyz ACC, %4, %2z\n\tvmaddw.xyz %0, %5, $vf0w" : "=j"(r) : "j"(m->r[0]), "j"(v), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3])); return r; }
static inline M4 *GetMat(struct X *p) { return p->vt[36].pfn((struct X *)((char *)p + p->vt[36].d)); }
// Classifies the winding of the path (same routine as Sly 2 func_001BC2F8): returns 2 for fewer than two points, 0 for a
// self-crossing turn pattern, otherwise 2/3/4 from the sign of the last non-straight turn.
int func_001E64A8(struct X *p)
{
    int cFlip, i, sPrev, sgn;
    M4 m;
    if (p->c < 2)
        return 2;
    cFlip = 0;
    i = 0;
    sPrev = 0;
    m = *GetMat(p);
    sgn = func_001E63B8(MulPt(&m, p->apos[0]), MulPt(&m, p->apos[1]));
    for (; i < p->c - 1; i++) {
        int i0 = func_001E66D8(p, i);
        int i1 = func_001E66D8(p, i0 + 1);
        int i2 = func_001E66D8(p, i1 + 1);
        qword a = MulPt(&m, p->apos[i0]);
        qword b = MulPt(&m, p->apos[i1]);
        qword c = MulPt(&m, p->apos[i2]);
        int s = func_001E63B8(b, c);
        int t;
        if (s) {
            if (s == -sgn)
                cFlip++;
        }
        sgn = s;
        t = func_001E6428(a, b, c);
        if (t) {
            if (t == -sPrev)
                return 0;
            sPrev = t;
        }
    }
    if (cFlip >= 3)
        return sPrev == 0;
    switch (sPrev) {
    case -1:
        return 4;
    case 1:
        return 3;
    }
    return 2;
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct VT { short d; short pad; void *pfn; };
struct X { char pad[0xC]; struct VT *vt; char pad2[0xE4 - 0x10]; qword *apos; };
int func_0022F198(struct X *p, float g, int a, int b);
int func_001E66D8(struct X *p, int i);
void func_0022E330(struct X *p, float g, qword *pv, int n);
int func_001ED1D0(void *pv, qword a, qword b, int k);
static inline qword MulPos(M4 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz ACC, %1, %5x\n\tvmadday.xyz ACC, %2, %5y\n\tvmaddaz.xyz ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]), "j"(v));
    return r;
}
// Path walk between two parameters g0 and g1 of path p (same routine as Sly 2 func_001BCAC0): walks the point list forward (or
// backward when fRev) and tests each segment against pv, once per pass; returns the pass whose walk is clear, 2 if neither.
int func_001E6CB8(struct X *p, void *pv, int fRev, float g0, float g1)
{
    int i0, r, pass, k, i1;
    i0 = func_0022F198(p, g0, 0, 0);
    i1 = func_0022F198(p, g1, 0, 0);
    for (pass = 0; pass < 2; pass++) {
        int i, iEnd, a;
        M4 m;
        qword v0, v1, q, v;
        switch (pass) {
        case 0: r = 0; k = 0; break;
        case 1: r = 1; k = 1; break;
        }
        if (fRev) {
            a = func_001E66D8(p, i0 + 1);
            iEnd = func_001E66D8(p, i1 + 1);
        } else {
            a = i0;
            iEnd = i1;
        }
        i = a;
        m = *((M4 *(*)(void *))p->vt[36].pfn)((char *)p + p->vt[36].d);
        func_0022E330(p, g0, &v0, 0);
        q = v0;
        while (i != iEnd) {
            v = MulPos(&m, p->apos[i]);
            if (func_001ED1D0(pv, q, v, k))
                goto next;
            if (fRev)
                i = func_001E66D8(p, i + 1);
            else
                i = func_001E66D8(p, i - 1);
            q = v;
        }
        func_0022E330(p, g1, &v1, 0);
        if (!func_001ED1D0(pv, q, v1, k))
            return r;
    next:;
    }
    return 2;
}

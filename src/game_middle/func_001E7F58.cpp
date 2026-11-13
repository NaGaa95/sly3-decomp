// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Merges n polygon objects into one new object: every source point (minus the closing one) is transformed by its owner's
// matrix into one array, the new object takes the points, is moved to their centroid (vt[34]) and the points are made
// relative to it; children attached to the sources are moved over and the sources are destroyed.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef union { qword q; float f[4]; } Vec;
struct CTX;
extern "C" CTX*func_001D2770(CTX*);
extern "C" void func_001D2798(CTX*,int);
struct CTX { CTX(){(void)func_001D2770(this);}~CTX(){func_001D2798(this,2);} };
struct AREQ { int cb; int align; AREQ(int c, int a) { cb = c; align = a; } };
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct DLI { DL *pdl; void **ppv; int ibDle; DLI *pdliNext; };
struct X;
struct VT { short d; short pad; void *pfn; };
struct X { int x0, x4, x8; VT *vt; char pad[0xD4 - 0x10]; int xD4; int c; char padDC[0xE4 - 0xDC]; qword *apos;
           char padE8[0x180 - 0xE8]; int x180; char pad184[0x1B0 - 0x184]; int x1B0; DL dl; char pad1C0[0x1C8 - 0x1C0]; X *x1C8; };
extern DLI *g_pdliFirst;
extern qword D_00317560;
extern DL D_0047A260;
extern "C" {
void *func_001D25B0(const AREQ &r);
X *func_001E7A60(void);
void func_001E7CA0(X *p, int n, qword *pts);
void func_001E7EF0(X *p, X *pNew);
void func_0011B028(DL *pdl, void *pv);
void func_0011AF60(DL *pdl, void *pv);
void func_0022DB08(X *p);
int func_001E64A8(X *p);
}
static inline void *Alloc(int cb) { return func_001D25B0(AREQ(cb, 0x10)); }
/* point * 4x4 matrix (xyz only, w from row 3) */
static inline qword MulPt(M4*m,qword*point){
 qword out;
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(out):"j"(m->r[0]),"j"(m->r[1]),"j"(m->r[2]),"j"(m->r[3]),"j"(*point));return out;
}
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline qword DivRef(qword v, const VU_FLOAT &s)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->pdl = pdl;
    pdli->ppv = (void **)pdl;
    pdli->ibDle = pdl->ibDle;
    pdli->pdliNext = g_pdliFirst;
    g_pdliFirst = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->ppv;
    pdli->ppv = (void **)((char *)pv + pdli->ibDle);
    return pv;
}

extern "C" void func_001E7F58(int n, X **ap)
{
    int c = 0;
    int i;
    qword *apos;
    X *pNew;
    for (int i0 = 0; i0 < n; i0++) c += ap[i0]->c - 1;
    CTX ctx;
    apos = (qword *)Alloc(c << 4);
    int iw = 0;
    for (int polygon = 0; polygon < n; polygon++) {
        X *px = ap[polygon];
        M4 m = *((M4 *(*)(X *))px->vt[36].pfn)((X *)((char *)px + px->vt[36].d));
        for (int j = 0; j < px->c - 1; j++) {
            qword *pw = &apos[iw++];
            *pw = MulPt(&m, &px->apos[j]);
        }
    }
    pNew = func_001E7A60();
    func_001E7CA0(pNew, c, apos);
    {
        qword sum = D_00317560;
        for (int sumIndex = pNew->c - 2; sumIndex >= 0; --sumIndex)
            sum = Add(sum, pNew->apos[sumIndex]);
        VT *vt = pNew->vt;
        X *target = (X *)((char *)pNew + vt[34].d);
        {
            qword center = DivRef(sum, VU_FLOAT((float)(pNew->c - 1)));
            ((void (*)(X *, qword))vt[34].pfn)(target, center);
            int pointIndex = pNew->c;
            while (--pointIndex >= 0)
                pNew->apos[pointIndex] = Sub(pNew->apos[pointIndex], center);
        }
    }
    for (i = 0; i < n; i++) {
        X *px = ap[i];
        if (px->x1B0) {
            DLI dli;
            X *pv;
            InitDli(&dli, &px->dl);
            while ((pv = (X *)PvNextDli(&dli)) != 0) {
                func_0011B028(&px->dl, pv);
                pv->x1C8 = 0;
                func_001E7EF0(pv, pNew);
            }
            ((void (*)(X *))px->vt[9].pfn)((X *)((char *)px + px->vt[9].d));
            func_0011AF60(&D_0047A260, px);
            g_pdliFirst = dli.pdliNext;
        } else {
            func_001E7EF0(px, pNew);
        }
    }
    pNew->xD4 = 1;
    func_0022DB08(pNew);
    pNew->x180 = func_001E64A8(pNew);
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// func_0020B280 (agent A92): Sly 3 form of Sly 2 ProjectRipgTransform__FP4RIPGfi (0x1CDF88, src/hand/func_001CDF88.c):
// bounds of a rip group from its children (min/max of their two corners), then center/radius when the group has an owner.
// Sly 3 drops the size growth step; field offsets moved. One pin: the low bound in vf4.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
typedef struct VT { struct { short d; short pad; void (*pfn)(void *); } a[16]; } VT;
typedef struct S {
    char pad0[0x14]; float time; char pad18[0x70 - 0x18]; qword cornerA; qword cornerB; char pad90[0xDC - 0x90];
    void *owner; char padE0[0xE8 - 0xE0]; VT *vt; char padEC[0x134 - 0xEC]; DL children; char pad140[0];
    union U lo; union U hi; union U center; float radius;
} S;
extern DLI *g_pdliFirst;
extern struct { float t; } g_clock;
extern const float D_00325930, D_00325934;
void func_0023DCA0(S *);
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
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
// a*k.x + b*k.x (the midpoint for k = 0.5).
static inline qword Mid(qword a, qword b, qword k) { qword r; __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(k)); return r; }
// Length of a vector in two steps (sum of squares, then sqrt).  The "memory" clobbers keep the stores around the steps in source order.
#define LEN1(d, one, v) __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v) : "memory")
#define LEN2(d) __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d) : : "memory")
void func_0020B280(S *p)
{
    DLI dli;
    union U lo, hi, t, half;
    // y/z of each bound are written through pointers (the original did too: it changes how the DLI fields are reloaded)
    union U *plo = &lo, *phi = &hi;
    S *q;
    InitDli(&dli, &p->children);
    plo->f[1] = plo->f[2] = D_00325930;
    lo.f[0] = D_00325930;
    phi->f[1] = phi->f[2] = D_00325934;
    hi.f[0] = D_00325934;
    while ((q = (S *)PvNextDli(&dli)) != 0) {
        if (q->time <= g_clock.t)
            q->vt->a[3].pfn((char *)q + q->vt->a[3].d);
        lo.q = Min(lo.q, Min(q->cornerA, q->cornerB));
        hi.q = Max(hi.q, Max(q->cornerA, q->cornerB));
    }
    if (p->owner) {
        float h = 0.5f;
        int r;
        register qword lv __asm__("vf4") = lo.q; /* pin: low bound in vf4 */
        qword k, mid, d, one, hv = hi.q;
        __asm__("qmtc2.ni %1,%0" : "=j"(k) : "r"(h));
        mid = Mid(lv, hv, k);
        half.q = k;
        p->lo.q = lv;
        LEN1(d, one, Sub(mid, hv));
        t.q = mid;
        LEN2(d);
        p->hi.q = hv;
        __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(d) : "memory");
        *(int *)&p->radius = r;
        p->center.q = mid;
        func_0023DCA0(p);
    }
    g_pdliFirst = dli.pdliNext;
}

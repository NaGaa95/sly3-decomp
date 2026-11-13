// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Recompute a group's bounds from its item list: run the update of every due item, accumulate the min/max of the
// items' two corner vectors, then (when active) store the box, the center and the bounding radius and notify.
// Same shape as Sly 2 func_001CDF88. The "memory" clobbers on the length steps and on the qmfc2 keep the stores in
// the original order around them (the center store ends up in the call's delay slot).
typedef int qword __attribute__((mode(TI)));
#define FLT_MAX 3.40282347e+38f
union UQ { qword q; float f[4]; };
struct VTE { short d; short pad; void *pfn; };
struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
struct Item {
    unsigned char pad0[0x14];
    float updateTime;
    unsigned char pad18[0x70 - 0x18];
    qword boundA;
    qword boundB;
    unsigned char pad90[0xE8 - 0x90];
    VTE *hooks;
};
struct Group {
    unsigned char pad0[0xDC];
    int active;
    unsigned char padE0[0x134 - 0xE0];
    DL items;
    qword boxMin;
    qword boxMax;
    qword center;
    union { float f; int bits; } radius;
};
struct CLOCK { float now; };
extern "C" {
extern DLI *D_0036AE94;
extern CLOCK D_0036BB98;
void func_0023DCA0(Group *group);
}
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_0036AE94;
    D_0036AE94 = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
// a * k.x + b * k.x
static inline qword Mid(qword a, qword b, qword k)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(k));
    return r;
}
// Vector length in two steps (sum of squares, then square root).
#define LEN1(d, one, v) __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v) : "memory")
#define LEN2(d) __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d) : : "memory")
extern "C" void func_0020B280(Group *self)
{
    DLI dli;
    UQ lo, hi, t, half;
    // y/z of each bound are written through pointers (changes how the DLI fields are reloaded, as in the original)
    UQ *plo = &lo, *phi = &hi;
    void *pv;
    InitDli(&dli, &self->items);
    plo->f[1] = plo->f[2] = FLT_MAX;
    lo.f[0] = FLT_MAX;
    phi->f[1] = phi->f[2] = -FLT_MAX;
    hi.f[0] = -FLT_MAX;
    while ((pv = PvNextDli(&dli)) != 0) {
        Item *item = (Item *)pv;
        if (item->updateTime <= D_0036BB98.now)
            ((void (*)(void *))item->hooks[3].pfn)((char *)item + item->hooks[3].d);
        lo.q = Min(lo.q, Min(item->boundA, item->boundB));
        hi.q = Max(hi.q, Max(item->boundA, item->boundB));
    }
    if (self->active) {
        float h = 0.5f;
        int r;
        qword k, mid, d, one, v, hv = hi.q;
        register qword lv asm("vf4") = lo.q; /* register pin: the original keeps the minimum corner in vf4 */
        __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(h));
        mid = Mid(lv, hv, k);
        half.q = k;
        self->boxMin = lv;
        v = Sub(mid, hv);
        LEN1(d, one, v);
        t.q = mid;
        LEN2(d);
        self->boxMax = hv;
        __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d) : "memory");
        self->radius.bits = r;
        self->center = mid;
        func_0023DCA0(self);
    }
    D_0036AE94 = dli.m_pdliNext;
}

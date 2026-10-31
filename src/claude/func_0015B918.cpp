// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct V4 { float x, y, z, w; } __attribute__((aligned(16)));
struct VTE { short d; short pad; void *pfn; };
struct LO { char pad[0xC]; VTE *pvt; char pad1[0x2C - 0x10]; unsigned char b2C; };
struct E { float g0; char pad[0x14 - 4]; VTE *pvt; };
struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
struct P { char pad[0x3E50]; DL dl; void *p3E5C; int x3E60; int c3E64; char pad2[0x3E70 - 0x3E68]; V4 av[4]; };
struct VU_VECTOR { qword q; VU_VECTOR(const VU_VECTOR &s) { q = s.q; } VU_VECTOR(const qword &v) { q = v; } };
extern "C" {
extern int D_00479390;
extern DLI *D_0036AE94;
int func_0015B820(P *p, V4 *av, int *pmask);
void func_0015B780(P *p);
void CopyAb(void *pvDst, void *pvSrc, int cb);
float func_0015B068(qword pos, int n, V4 *av);
void func_0015B728(P *p, E *pe);
void func_0015B5E0(P *p, E *pe);
void func_0015B580(P *p, E *pe);
void func_0015B918(P *p);
}
static inline float Dist(VU_VECTOR a, VU_VECTOR b)
{
    qword d, one;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a.q), "j"(b.q));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "0"(d));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "0"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline M4 *Mat(LO *plo) { return ((M4 *(*)(void *))plo->pvt[36].pfn)((char *)plo + plo->pvt[36].d); }
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

void func_0015B918(P *p)
{
    V4 av[2];
    int mask;
    int c;
    float dMax;
    if (D_00479390)
        return;
    c = func_0015B820(p, av, &mask);
    if (mask != p->x3E60 || c != p->c3E64) {
    reset:
        dMax = 0.0f;
        func_0015B780(p);
        p->c3E64 = c;
        p->x3E60 = mask;
        CopyAb(p->av, av, c * 16);
    } else {
        int i;
        dMax = 0.0f;
        for (i = 0; i < c; i++) {
            float d = Dist(*(qword *)&av[i], *(qword *)&p->av[i]);
            if (dMax < d)
                dMax = d;
        }
        if (500.0f < dMax)
            goto reset;
    }
    {
        DLI dli;
        E *pe;
        InitDli(&dli, &p->dl);
        while ((pe = (E *)PvNextDli(&dli)) != p->p3E5C) {
            LO *plo = ((LO *(*)(void *))pe->pvt[1].pfn)((char *)pe + pe->pvt[1].d);
            int f;
            if (!(mask & plo->b2C))
                f = 0;
            else {
                float g = func_0015B068(Mat(plo)->r[3], p->c3E64, p->av);
                if (__builtin_fabsf(g - pe->g0) - dMax > 500.0f)
                    func_0015B728(p, pe);
                else
                    g = func_0015B068(Mat(plo)->r[3], c, av);
                f = g < pe->g0;
            }
            if (f)
                func_0015B5E0(p, pe);
            else
                func_0015B580(p, pe);
        }
        D_0036AE94 = dli.m_pdliNext;
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct V4 { float x, y, z, w; } __attribute__((aligned(16)));
struct VTE { short d; short pad; void *pfn; };
struct SO { char pad[0xC]; VTE *pvt; char pad1[0x28 - 0x10]; long grf; char pad2[0x34 - 0x30]; float g34; };
struct SOX { char pad[0x2C]; unsigned char b2C; };
struct ITEM { SO *pso; };
struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
struct P { char pad[0x3DE8]; DL dl; void *pvStop; DL dl2; int x3E04; int c3E08; char pad2[0x3E10 - 0x3E0C]; V4 av[4]; };
struct VU_VECTOR { qword q; VU_VECTOR(const VU_VECTOR &s) { q = s.q; } VU_VECTOR(const qword &v) { q = v; } };
extern "C" {
extern int D_00479390;
extern DLI *D_0036AE94;
int func_0015AF58(P *p, int *pmask, V4 *av);
void func_0015AF48(P *p);
void func_001D2898(void *pvDst, void *pvSrc, int cb);
float func_0015B068(qword pos, int n, V4 *av);
void func_0015AE18(P *p, void *pv);
int func_0011B0C0(DL *pdl, void *pv);
void func_0011AF60(DL *pdl, void *pv);
void func_0011B028(DL *pdl, void *pv);
void func_0015B0E8(P *p);
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
static inline M4 *Mat(SO *pso) { return ((M4 *(*)(void *))pso->pvt[36].pfn)((char *)pso + pso->pvt[36].d); }
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

void func_0015B0E8(P *p)
{
    V4 av[4];
    int mask;
    int c;
    float dMax;
    if (D_00479390)
        return;
    c = func_0015AF58(p, &mask, av);
    if (mask != p->x3E04 || c != p->c3E08) {
    reset:
        dMax = 0.0f;
        func_0015AF48(p);
        p->c3E08 = c;
        p->x3E04 = mask;
        func_001D2898(p->av, av, c << 4);
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
        void *pv;
        InitDli(&dli, &p->dl);
        while ((pv = PvNextDli(&dli)) != p->pvStop) {
            SO *pso = ((ITEM *)pv)->pso;
            int fIn;
            switch ((int)((pso->grf << 12) >> 60)) {
            case 2:
                fIn = 0;
                func_0015AE18(p, pv);
                break;
            case 1:
                fIn = 1;
                func_0015AE18(p, pv);
                break;
            case 0:
                if (!(p->x3E04 & ((SOX *)pso)->b2C)) {
                    fIn = 0;
                    func_0015AE18(p, pv);
                } else {
                    float g = func_0015B068(Mat(pso)->r[3], p->c3E08, p->av);
                    if (__builtin_fabsf(g - pso->g34) - dMax > 500.0f)
                        func_0015AE18(p, pv);
                    else
                        g = func_0015B068(Mat(pso)->r[3], c, av);
                    fIn = g < pso->g34;
                }
                break;
            }
            if (fIn != func_0011B0C0(&p->dl2, pv)) {
                if (fIn) {
                    func_0011AF60(&p->dl2, pv);
                    ((void (*)(void *))pso->pvt[25].pfn)((char *)pso + pso->pvt[25].d);
                } else {
                    ((void (*)(void *))pso->pvt[24].pfn)((char *)pso + pso->pvt[24].d);
                    func_0011B028(&p->dl2, pv);
                }
            }
        }
        D_0036AE94 = dli.m_pdliNext;
    }
}

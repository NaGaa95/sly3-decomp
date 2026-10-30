// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Choose / validate the current attack for the owner and blend its facing (owns rodata 0x31FA30). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VTE { short delta; short pad; void *pfn; };
struct LM { float gMin, gMax; };
struct PS { char pad[8]; float g8; char padC[0x18 - 0xC]; unsigned int grf; char pad1C[0x2C - 0x1C]; struct VTE *vt; };
struct A { char pad[0x40]; int x40; int x44; int x48; int x4C; int x50; int x54; int x58; int x5C;
    char pad60[0x6C - 0x60]; int x6C; float g70; float g74; char pad78[0xF0 - 0x78]; int xF0; char padF4[0xFC - 0xF4];
    struct A *pnext; };
struct D { char pad[0x14]; void *p14; char pad18[0x1C - 0x18]; float g1C; };
struct O { char pad[0xC]; struct VTE *vt; char pad10[0x134 - 0x10]; struct PS *pps; char pad138[0x1A0 - 0x138]; qword q1A0;
    char pad1B0[0x110C - 0x1B0]; float g110C; char pad1110[0x11C4 - 0x1110]; int x11C4; };
struct T { struct O *po; int x4; int x8; struct A *pa; int x10; float g14; struct D *pd; struct A *pa1C;
    char pad20[0x2C - 0x20]; int x2C; int x30; };
extern struct LM D_00341FF0;
int func_00139A40(void *);
int func_0013ADE0(struct T *);
int func_00139928(struct A *);
void func_0013A678(struct T *, struct A *, int);
void func_0013A5B8(struct T *);
void func_0013AB30(struct T *);
int func_00138AC8(struct D *);
void func_0024E920(struct O *, int);
qword func_0024F278(struct O *, struct D *, float);
float *func_00136880(void *, int);
qword func_0011FD70(float, float, float);
qword func_001C94E8(void *, void *, qword);
#define VCALL(po, n, T) ((T)(po)->vt[n].pfn)((char *)(po) + (po)->vt[n].delta
static inline qword Splat(float g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static inline qword MulX(qword a, qword b) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Blend(qword a, qword sa, qword b, qword sb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %0x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(sb), "0"(sa));
    return r;
}
static inline qword MulX0(qword a, qword b) { qword r; __asm__("vmulx.xyzw %0, %1, %0x" : "=j"(r) : "j"(a), "0"(b)); return r; }
static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        g = gMin;
    else if (gMax < g)
        g = gMax;
    return g;
}

void func_0013A178(struct T *p)
{
    static const float ag[3] = { 0.5f, 0.5f, 0.0f };
    struct PS *pps = p->po->pps;
    int mask = func_00139A40(VCALL(p->po, 105, void *(*)(void *))));
    if (func_0013ADE0(p) && VCALL(p->po, 113, int (*)(void *, int)), 2)) {
        struct A *paBest = 0;
        int nPri = 0x80000001;
        int nBest = 0;
        struct A *pa;
        for (pa = p->pa1C; pa; pa = pa->pnext) {
            int n;
            if ((mask & pa->x40) != mask)
                continue;
            if (pa->x6C < nPri)
                continue;
            if (pa->x48 && !(pps->grf & pa->x48))
                continue;
            if (pa->x4C && !(~pps->grf & pa->x4C))
                continue;
            n = 0;
            if (pa->x44) {
                n = VCALL(pps, 1, int (*)(void *, int, float)), pa->x44, pa->g70);
                if (n != pa->x44)
                    continue;
            }
            if (!func_00139928(pa))
                continue;
            nPri = pa->x6C;
            nBest = n;
            paBest = pa;
        }
        if (paBest) {
            VCALL(pps, 2, void (*)(void *, int)), nBest);
            func_0013A678(p, paBest, 0);
        }
    }
    func_0013A5B8(p);
    if (p->pa) {
        VCALL(pps, 2, void (*)(void *, int)), p->pa->xF0);
        if (p->pa && (unsigned)p->x4 < 2) {
            struct A *pa = p->pa;
            if ((mask & pa->x50) || (pps->grf & pa->x58) || (~pps->grf & pa->x5C) ||
                VCALL(pps, 1, int (*)(void *, int, float)), pa->x54, pa->g70))
                func_0013AB30(p);
            else if (!p->pd || func_00138AC8(p->pd))
                func_0013AB30(p);
        }
    }
    if (p->x4 == 0) {
        if (p->x10 && p->po->x11C4 == 4)
            func_0024E920(p->po, p->x10);
    }
    switch (p->x4) {
    case 0:
    case 2: {
        float g;
        U s;
        struct O *po = p->po;
        struct D *pd = p->pd;
        qword v = func_0024F278(po, pd, pd->g1C);
        s.q = Splat(-1.0f);
        po->q1A0 = MulX(v, s.q);
        if (!p->x2C && !p->x30)
            return;
        if (p->x30)
            g = 1.0f;
        else {
            float *pa0 = func_00136880(p->pd->p14, 0x2A0);
            float *pa1 = func_00136880(p->pd->p14, 0x2A2);
            float g0 = *pa0;
            float t = (p->pd->g1C - g0) / (*pa1 - g0);
            g = GClamp(ag[0] + t * (ag[1] + t * ag[2]), D_00341FF0.gMin, D_00341FF0.gMax);
        }
        {
            qword dir = func_001C94E8(0, p->po, func_0011FD70(p->po->g110C, pps->g8 * p->pa->g74, 0.0f));
            qword nd, r;
            s.q = Splat(-1.0f);
            nd = MulX0(dir, s.q);
            s.q = Splat(1.0f - g);
            r = Blend(p->po->q1A0, s.q, nd, Splat(g));
            s.q = Splat(g);
            p->po->q1A0 = r;
        }
    }
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_00139DC0.cpp (Sly 3 offsets/addresses).
// func_0014A2B0 (0x139DC0): CPU fallback of func_00149FC0 (taken when p->x160 != 0 or D_00342DB0 is set). For every particle
// batch in the DLI list at p->dl it copies the live particles (b.w > clock.t) from abuf[i] to abuf[(i + 1) & 1]: x160 0 =
// velocity transformed by func_00179CC0's matrix, 1 = plain copy, 2 = func_00118558 path; x43C == 2 updates c.w through
// RadNormalize. It accumulates the bounding box in vMin/vMax and sets p->vF0 = centre, p->g100 = radius + p->g120 (or calls
// virtual slot 9 when p->c444 drops to 0).
// The case-2 destination pointers pa/pbb are declared at the loop top around pcd (order a, b, c)
// -> loop.c creates the a/b/c givs in the target's order (s7 = a, s6 = b, pcd from t1).
typedef int qword __attribute__((mode(TI)));
/* FLT_MAX / -FLT_MAX literals: in the original unit's shared literal row 0x320200 (with func_00148890's D_00320200), referenced by address */
extern "C" const float D_0032020C, D_00320210;
typedef union { qword q; struct { float x, y, z, w; } v; } VEC;
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j,j"(q) : "r,m"(f), "i,r"(0)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Mid(qword a, qword b, VU_FLOAT h)
{
    qword c;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(c) : "j"(a), "j"(b), "j"(h.q));
    return c;
}
struct M4 { qword r[4]; };
struct VECTOR { union { struct { float x, y, z; } v; qword q; }; };

struct DL { void *head; void *tail; int ibDle; };
struct DLI { struct DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; };
struct BUF { VEC a[0x2B]; VEC b[0x2B]; VEC c[0x2B]; char pad[0x840 - 0x810]; };
struct E { qword v0; qword v10; };
struct Q { struct BUF abuf[2]; int i; int c; struct E *ae; };
struct VT { short d; short pad; void (*pfn)(void *); };
struct P {
    char pad0[0xC]; struct VT *pvt; char pad10[0xE0 - 0x10]; qword vF0; float g100; char pad104[0x110 - 0xF4]; float g120;
    char pad124[0x150 - 0x114]; int x160; char pad164[0x160 - 0x154]; char x170[0x42C - 0x160]; int x43C; int pad440; int c444; struct DL dl;
};
struct CLOCK { float t; float dt; };
#define CA(p) ((VEC *)((int)(p) - 0x560))
#define CB(p) ((VEC *)((int)(p) - 0x2B0))
extern "C" struct CLOCK g_clock;
extern struct DLI *D_0036AE94;
extern int D_00342DB0;
extern "C" {
void func_00149FC0(struct P *p);
struct M4 func_00179CC0(void *p);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, int);
float func_0011E3B8(float g);
void func_001495F8(struct Q *pq);
void func_0014A2B0(struct P *p);
}

static __inline__ void SetV(VEC *pv, float g)
{
    pv->q = 0;
    pv->v.z = pv->v.y = pv->v.x = g;
}
static __inline__ void InitDli(struct DLI *pdli, struct DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_0036AE94;
    D_0036AE94 = pdli;
}
static __inline__ void *PvNextDli(struct DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
static __inline__ qword MulPoint(struct M4 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]), "j"(v));
    return r;
}

void func_0014A2B0(struct P *p)
{
    struct M4 m;
    if (p->x160 == 0) {
        if (D_00342DB0 == 0) {
            func_00149FC0(p);
            return;
        }
        m = func_00179CC0(p->x170);
    }
    {
    VECTOR vMin = {{{D_0032020C, D_0032020C, D_0032020C}}};
    VECTOR vMax = {{{D_00320210, D_00320210, D_00320210}}};
    struct DLI dli;
    struct Q *pq;
    InitDli(&dli, &p->dl);
    while ((pq = (struct Q *)PvNextDli(&dli)) != 0) {
        int i, iNext, j, cDead;
        struct BUF *pb, *pbn;
        j = 0;
        cDead = 0;
        pb = &pq->abuf[pq->i];
        iNext = (pq->i + 1) & 1;
        pbn = &pq->abuf[iNext];
        for (i = 0; i < pq->c; i++) {
            VEC *pcs = &pb->c[i];
            qword *pa = &pbn->a[j].q;
            qword *pbb = &pbn->b[j].q;
            VEC *pcd = &pbn->c[j];
            float t = g_clock.t;
            float tEnd = CB(pcs)[0].v.w;
            if (tEnd <= t) {
                cDead++;
                continue;
            }
            switch (p->x160) {
            case 0: {
                qword v = MulPoint(&m, CB(pcs)[0].q);
                CB(pcd)[0].q = v;
                CA(pcd)[0].q = AddScaled(CA(pcs)[0].q, v, VU_FLOAT(g_clock.dt));
                break;
            }
            case 1: {
                qword v = CB(pcs)[0].q;
                CB(pcd)[0].q = v;
                CA(pcd)[0].q = AddScaled(CA(pcs)[0].q, v, VU_FLOAT(g_clock.dt));
                break;
            }
            case 2: {
                float rem = tEnd - t;
                float dt = g_clock.dt;
                func_00118558(rem, dt < rem ? dt : rem, 1.0f, CA(pcs)[0].q, CB(pcs)[0].q, pq->ae[i].v0, pq->ae[i].v10, pa, pbb, 0);
                if (j != i)
                    pq->ae[j] = pq->ae[i];
                break;
            }
            }
            CA(pcd)[0].v.w = CA(pcs)[0].v.w;
            CB(pcd)[0].v.w = CB(pcs)[0].v.w;
            *pcd = *pcs;
            if (p->x43C == 2)
                pcd->v.w = func_0011E3B8(pcs->v.w + pcs->v.z * g_clock.dt);
            *(qword *)&vMin = Min(*(qword *)&vMin, CA(pcd)[0].q);
            *(qword *)&vMax = Max(*(qword *)&vMax, CA(pcd)[0].q);
            j++;
        }
        __asm__("" : : "r"(cDead));
        pq->c -= cDead;
        p->c444 -= cDead;
        if (pq->c <= 0)
            func_001495F8(pq);
        else
            pq->i = iNext;
    }
    if (p->c444 <= 0) {
        struct VT *pvt = p->pvt;
        pvt[9].pfn((char *)p + pvt[9].d);
    } else {
        qword c, d, one, l;
        float g;
        c = Mid(*(qword *)&vMin, *(qword *)&vMax, VU_FLOAT(0.5f));
        p->vF0 = c;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(c), "j"(*(qword *)&vMax));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
        p->g100 = g + p->g120;
    }
    D_0036AE94 = dli.m_pdliNext;
    }
}

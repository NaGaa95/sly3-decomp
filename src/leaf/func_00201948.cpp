// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Particle batch update (variant of func_00149FC0 that takes the transform): DMA double-buffered microprogram pass over the batch list at
// p->dl, accumulating the bounding box; returns 1 and sets the bounding sphere (centre, radius + g) while particles remain, 0 otherwise.
typedef int qword __attribute__((mode(TI)));
#define FLT_MAX 3.40282347e+38f
struct VECTOR { union { struct { float x, y, z; } v; qword q; }; };
struct M4 { qword a[4]; };
struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
struct BUF { char ab[0x2B0]; char ab2[0x560 - 0x2B0]; char ab3[0x840 - 0x560]; };
struct Q { BUF abuf[2]; int i; int c; };
struct SBE { int cb; char *pv; };
struct SPRBUF { unsigned long *aqw; char *pv; SBE a[8]; int c; int state; };
struct VU_FLOAT { qword qw; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); } VU_FLOAT() {} };
struct VU_FLOATM { qword qw; };

struct Shape { char pad0[0x24]; int count; };
struct Kind { char pad0[0x1C]; Shape *shape; };
struct PX {
    int pad0; Kind *kind; char pad8[0x2C - 8]; float radius; qword centre; char pad40[0x50 - 0x40]; DL dl; int count; char pad60[0x80 - 0x60]; float extent;
};
extern "C" {
extern DLI *D_0036AE94;
extern float D_0036BB9C; /* g_clock.dt */
extern int D_00349870;
extern SPRBUF D_00475280[2];
extern void *D_0036BD44;
}
extern "C" {
void func_0024B578(int cb, ...);
void func_0024B708(void *pv, ...);
void func_00293920(int);

void func_0024B8E8(void);
int func_00149E58(M4 *pm, VU_FLOATM dt, char *a, char *b, char *c, int n, int d, VECTOR *pvMin, VECTOR *pvMax);

void func_001495F8(Q *pq);
int sceDmaSync(void *pch, int mode, int timeout);
int func_00201948(PX *p, M4 *pm);
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
static inline VU_FLOATM VuFloatDt()
{
    VU_FLOATM v;
    __asm__("lw %0, %1" : "=r"(v.qw) : "m"(D_0036BB9C));
    return v;
}
static inline char *PvSprBuf(int i)
{
    return D_00475280[D_00349870].a[i].pv;
}
static inline void Kick(Q *pq)
{
    BUF *pb = &pq->abuf[pq->i];
    func_0024B578(pq->c * 16, pb, pq->c * 16, pb->ab2, pq->c * 16, pb->ab3, 0, 0);
}
static inline qword QwMid(const qword &a, const qword &b, const VU_FLOAT &g)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(a), "j"(b), "j"(g.qw));
    return qw;
}
static inline qword QwSub(const qword &qw0, const qword &qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwLength(const qword &v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GFromQw(const qword &qw)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(qw)); /* mtc1 from a qword: gcc emits the qmfc2 */
    return g;
}
int func_00201948(PX *p, M4 *pm)
{
    VECTOR vMin = {{{FLT_MAX, FLT_MAX, FLT_MAX}}};
    VECTOR vMax = {{{-FLT_MAX, -FLT_MAX, -FLT_MAX}}};
    {
    DLI dli;
    Q *pq;
    InitDli(&dli, &p->dl);
    pq = (Q *)PvNextDli(&dli);
    int d = p->kind->shape->count;
    {
        BUF *pb = &pq->abuf[pq->i];
        func_00293920(0);
        func_0024B578(pq->c * 16, pb, pq->c * 16, pb->ab2, pq->c * 16, pb->ab3, 0, 0);
    }
    while (pq) {
        Q *pqNext;
        int n, i;
        func_0024B8E8();
        pqNext = (Q *)PvNextDli(&dli);
        if (pqNext) Kick(pqNext);
        n = func_00149E58(pm, VuFloatDt(), PvSprBuf(0), PvSprBuf(1), PvSprBuf(2), pq->c, d, &vMin, &vMax);
        i = (pq->i + 1) & 1;
        {
            BUF *pb = &pq->abuf[i];
            func_0024B708(pb, pb->ab2, pb->ab3, 0);
        }
        pq->c -= n;
        p->count -= n;
        if (pq->c <= 0) func_001495F8(pq);
        else pq->i = i;
        pq = pqNext;
    }
    sceDmaSync(D_0036BD44, 0, 0);
    if (p->count > 0) {
        qword c = QwMid(vMin.q, vMax.q, VU_FLOAT(0.5f));
        p->centre = c;
        float g = GFromQw(QwLength(QwSub(c, vMax.q)));
        p->radius = g + p->extent;
        D_0036AE94 = dli.m_pdliNext;
        return 1;
    } else {
        D_0036AE94 = dli.m_pdliNext;
        return 0;
    }
    }
}

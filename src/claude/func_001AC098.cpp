// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"
#include "../P2/input_interface.h"
#include "input_query_api.h"
struct VTE { short delta, pad; void *fn; };
struct M4 { qword r[4]; };
struct M3 { qword r[3]; };
struct XF { char pad0[0x30]; qword pos; };
struct LO { char pad0[0xC]; VTE *vt; };
struct HND { char pad0[0xC]; VTE *vt; char pad10[0x15C - 0x10]; LO *plo; float g160; float g164; };
struct SOPHYS { char pad0[0x80]; union { qword q; float f[4]; } dvGravity; };
struct OBJ { char pad0[0xC]; VTE *vt; };
struct X11B4 { char pad0[0x40C]; int n40C; };
union UQ { qword q; float f[4]; };
struct JTAIR { char pad0[0x50]; UQ v50; char pad60[0x118 - 0x60]; OBJ *p118; int pad11C; qword q120; };
struct JT {
    char pad0[0xC];
    VTE *vt;
    char pad10[0xD8 - 0x10];
    SOPHYS *psophys;
    char padDC[0x134 - 0xDC];
    INPUT_INTERFACE *pctl;
    char pad138[0x218 - 0x138];
    int n218;
    char pad21C[0x260 - 0x21C];
    UQ posHang;
    char pad270[0x320 - 0x270];
    JTAIR jtair;
    char pad450[0x500 - 0x450];
    char jtgrab[8];
    int nGrabState;
    char pad50C[0xE40 - 0x50C];
    char jtE40[0xF60 - 0xE40];
    char jtmode[0x1010 - 0xF60];
    char jt1010[0x10DC - 0x1010];
    void *p10DC;
    char pad10E0[0x10F8 - 0x10E0];
    int n10F8;
    char pad10FC[0x1108 - 0x10FC];
    void *plookup;
    char pad110C[0x113C - 0x110C];
    void *pasega;
    void *psma;
    char pad1144[0x11B4 - 0x1144];
    X11B4 *p11B4;
    int pad11B8;
    int n11BC;
    char pad11C0[0x1290 - 0x11C0];
    char jt1290[0x13E8 - 0x1290];
    int fBlock;
    char pad13EC[0x19E0 - 0x13EC];
    int jts;
    float tJts;
    int jtbs;
    char pad19EC[0x19F4 - 0x19EC];
    HND *phnd;
    char pad19F8[0x1E54 - 0x19F8];
    float g1E54;
    float g1E58;
    char pad1E5C[0x1E90 - 0x1E5C];
    char jt1E90[4];
};
struct POLY { float a, b, c; };
struct LM { float lo, hi; };
extern "C" {
extern float D_0036BB98;
extern qword D_003224D0;
extern qword D_00317530;
extern qword D_00317560;
extern POLY D_003224E0;
extern LM D_00341FF0;
void func_001ADDD0(JT *, int, int);
void func_001B7268(void *, int, void *, void *, float);
int func_002503C8(JT *, float);
int func_001398F0(void *);
int func_00156998(JT *);
int func_00173428(void *);
int func_00153290(JT *, int);
void func_001BDA88(void *, int, void *);
void func_001B5170(void *);
int func_001F4430(JT *);
int func_001B04A0(JT *);
int func_00138AC8(void *);
int func_00239CC0(void *);
unsigned int func_00154798(JT *, int);
int func_0013B500(LO *, int);
float func_0022DFD8(LO *);
void func_0022E330(LO *, qword *, void *, float);
qword func_001C9428(void *, HND *, qword);
M3 func_0011C8C0(float, qword);
qword func_00212480(float, qword, qword, qword);
int func_0011EA28(float, float, float, float *);
void func_0028F680(XF *, int, M4 *, M4 *, float);
M4 func_0011D768(const M4 &);
M4 func_0011D558(const M4 &, const M4 &);
qword func_00212628(qword, qword, qword, float);
void func_001B9020(void *);
void func_001B27D8(void *);
void func_001C2A18(void *);
void func_00271F78(void *);
void func_001408B0(void *);
void func_001BF1F8(void *);
void func_001AC098(JT *pjt);
}
static inline XF *XfOf(LO *p) { VTE *e = &p->vt[36]; return ((XF *(*)(void *))e->fn)((char *)p + e->delta); }
static inline XF *JtXf(JT *p) { VTE *e = &p->vt[36]; return ((XF *(*)(void *))e->fn)((char *)p + e->delta); }
static inline M4 *HndMat(HND *p) { VTE *e = &p->vt[36]; return ((M4 *(*)(void *))e->fn)((char *)p + e->delta); }
static inline int Allowed(JT *p, int k) { VTE *e = &p->vt[113]; return ((int (*)(void *, int))e->fn)((char *)p + e->delta, k); }
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline float GEvalPoly(POLY *p, float g) { return p->a + g * (p->b + g * p->c); }
static inline float GLimitLm(LM *plm, float g)
{
    float lo = plm->lo, hi = plm->hi;
    if (g < lo)
        g = lo;
    else if (hi < g)
        g = hi;
    return g;
}
static inline qword QwSubJ(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b), "j"(a));
    return r;
}
static inline qword QwSub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword QwTransformPos(M4 *pmat, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(pmat->r[0]), "j"(pmat->r[1]), "j"(pmat->r[2]), "j"(pmat->r[3]), "j"(v));
    return r;
}
static inline qword QwTransformPosR(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline qword QwRotateVecAt(M3 *pmat, qword *pv)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(*pv), "j"(pmat->r[0]), "j"(pmat->r[1]), "j"(pmat->r[2]));
    return r;
}
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
static inline qword QwScaleX(qword v, VU_FLOAT g)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(g.q));
    return r;
}
static inline qword QwMul(qword a, qword b)
{
    qword r;
    __asm__("vmul.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

void func_001AC098(JT *pjt)
{
    int jtsOld, jtbsOld;
    do {
        jtsOld = pjt->jts;
        jtbsOld = pjt->jtbs;
        switch (jtsOld) {
        case 8: {
            int nState = pjt->nGrabState;
            if (nState < 5) {
                if (nState >= 3 || nState == 1)
                    break;
                goto fell;
            }
            if (nState != 12)
                goto fell;
            break;
        }
        case 23:
            if (!func_001398F0(pjt->p10DC) && !pjt->n10F8)
                break;
        case 0: case 1: case 2: case 6: case 10: case 11: case 18:
        fell:
            if (func_002503C8(pjt, 0.1f))
                func_001B7268(&pjt->jtair, 0, 0, 0, 1.0f);
            break;
        }
        switch (pjt->jts) {
        case 3:
            func_001B9020(&pjt->jtair);
            break;
        case 8:
            func_001B27D8(pjt->jtgrab);
            break;
        case 5:
            func_001C2A18(pjt->jtE40);
            break;
        case 18:
            func_00271F78(pjt->jt1290);
            break;
        case 7:
            func_001408B0(pjt->jt1E90);
            break;
        case 9:
            func_001BF1F8(pjt->jt1010);
            break;
        case 23:
            if (func_001398F0(pjt->p10DC)) {
                if (0.0f < pjt->pctl->leftAmount || pjt->pctl->Query(0.1f, 0x40))
                    func_001ADDD0(pjt, 0, -1);
            }
            break;
        case 0: case 1: case 2: case 10:
            if (func_00156998(pjt)) {
                func_001ADDD0(pjt, 0, -1);
            } else if (func_001A7A80(pjt->pctl, 0x40, 0.1f)) {
                int blocked = pjt->plookup && func_00173428(pjt->plookup);
                if (blocked)
                    func_001B7268(&pjt->jtair, 0x11, 0, 0, 1.0f);
                else
                    func_001B7268(&pjt->jtair, 1, 0, 0, 1.0f);
            } else if (!(pjt->pctl->held18 & 8) && !pjt->fBlock && func_00153290(pjt, 0)) {
                func_001ADDD0(pjt, 6, 4);
            } else if (pjt->pctl->Query(0.15f, 0x400) && 0.1f < D_0036BB98 - pjt->tJts && Allowed(pjt, 3)) {
                func_001ADDD0(pjt, 0, -1);
                pjt->pctl->Consume(0x400);
                func_001BDA88(pjt->jtmode, 0, 0);
            } else {
                int blocked = pjt->plookup && func_00173428(pjt->plookup);
                if (!blocked && pjt->n11BC == 3 && pjt->p11B4->n40C == 2 && func_001A7A80(pjt->pctl, 0x20, 0.15f)) {
                    func_001ADDD0(pjt, 11, -1);
                } else if (func_001A7A80(pjt->pctl, 0x20, 0.2f)) {
                    func_001B5170(pjt->jtgrab);
                } else {
                    float amount = pjt->pctl->leftAmount;
                    if (pjt->jts == 0 ? 0.1f < amount : 0.0f < amount) {
                        int blocked2 = pjt->plookup && func_00173428(pjt->plookup);
                        if (blocked2)
                            func_001ADDD0(pjt, 1, -1);
                        else if ((pjt->pctl->held18 & 8) || pjt->fBlock)
                            func_001ADDD0(pjt, 2, -1);
                        else if (pjt->n11BC == 3)
                            func_001ADDD0(pjt, 10, -1);
                        else
                            func_001ADDD0(pjt, 1, -1);
                    } else {
                        int blocked2 = pjt->plookup && func_00173428(pjt->plookup);
                        if (blocked2)
                            func_001ADDD0(pjt, 0, -1);
                        else if (pjt->n11BC == 3)
                            func_001ADDD0(pjt, 10, -1);
                        else
                            func_001ADDD0(pjt, 0, -1);
                    }
                }
            }
            break;
        case 19:
            if ((float)func_001F4430(pjt) <= 0.0f)
                func_001ADDD0(pjt, 0, -1);
            else if (pjt->n218 && func_001A7A80(pjt->pctl, 0x40, 0.1f))
                func_001B7268(&pjt->jtair, 1, 0, 0, 1.0f);
            else if (func_001A7A80(pjt->pctl, 0x20, 0.2f))
                func_001B5170(pjt->jtgrab);
            else if (func_001B04A0(pjt))
                func_001ADDD0(pjt, 0, -1);
            break;
        case 6:
            if (func_00156998(pjt)) {
                func_001ADDD0(pjt, 6, 4);
            } else if ((pjt->pctl->held18 & 8) || pjt->fBlock || !func_00153290(pjt, 1)) {
                func_001ADDD0(pjt, 0, -1);
            } else if (func_001A7A80(pjt->pctl, 0x40, 0.1f)) {
                func_001B7268(&pjt->jtair, 1, 0, 0, 1.0f);
            } else if (pjt->pctl->Query(0.15f, 0x400) && 0.1f < D_0036BB98 - pjt->tJts && Allowed(pjt, 3)) {
                func_001ADDD0(pjt, 6, 4);
                pjt->pctl->Consume(0x400);
                func_001BDA88(pjt->jtmode, 0, 0);
            } else if (func_001A7A80(pjt->pctl, 0x20, 0.2f)) {
                func_001B5170(pjt->jtgrab);
            } else if (0.0f < pjt->pctl->leftAmount) {
                func_001ADDD0(pjt, 6, 5);
            } else {
                func_001ADDD0(pjt, 6, 4);
            }
            break;
        case 4:
            if (0.25f < D_0036BB98 - pjt->tJts) {
                if (func_001A7A80(pjt->pctl, 0x40, 0.25f))
                    func_001B7268(&pjt->jtair, 2, 0, 0, 1.0f);
            }
            break;
        case 13:
            if (!pjt->pasega || func_00138AC8(pjt->pasega))
                func_001ADDD0(pjt, 0, -1);
            break;
        case 15:
            if (!pjt->pasega || !func_00138AC8(pjt->pasega)) {
                if (!pjt->psma)
                    break;
                if (!func_00239CC0(pjt->psma))
                    break;
            }
            func_001ADDD0(pjt, 0, -1);
            break;
        case 17:
            if (func_001A7A80(pjt->pctl, 0x40, 0.25f)) {
                VECTOR4 vTarget;
                if (pjt->phnd->plo && func_0013B500(pjt->phnd->plo, 9)) {
                    LO *pshape = pjt->phnd->plo;
                    func_0022E330(pshape, (qword *)&vTarget, 0, func_0022DFD8(pshape) * (0.5f - pjt->g1E54 * 0.5f));
                } else {
                    VECTOR4 vLocal;
                    if (pjt->phnd->plo)
                        *(qword *)&vLocal = func_001C9428(0, pjt->phnd, XfOf(pjt->phnd->plo)->pos);
                    else
                        *(qword *)&vLocal = D_003224D0;
                    M3 mat;
                    mat = func_0011C8C0(pjt->g1E54 * pjt->phnd->g160, D_00317530);
                    *(qword *)&vTarget = QwTransformPos(HndMat(pjt->phnd), QwRotateVecAt(&mat, (qword *)&vLocal));
                }
                float gHalf = 0.5f;
                qword qwVel = func_00212480(gHalf, JtXf(pjt)->pos, QwSub(*(qword *)&vTarget, pjt->posHang.q), pjt->psophys->dvGravity.q);
                float at[2];
                at[0] = 0.0f;
                float b = PackedVectorZ(qwVel) + 1.0f;
                float a = pjt->psophys->dvGravity.f[2] * gHalf;
                int c = func_0011EA28(a, b, PackedVectorZ(JtXf(pjt)->pos) + pjt->posHang.f[2] - vTarget.z, at);
                int n = c;
                if (c <= 1) n = 1;
                HND *phnd = pjt->phnd;
                float t = GMin(phnd->g164, at[n - 1]);
                LO *ploT = phnd->plo;
                XF *pxf;
                if (ploT) {
                    VTE *e = &ploT->vt[37];
                    pxf = ((XF *(*)(void *, int))e->fn)((char *)ploT + e->delta, 0);
                } else {
                    VTE *e = &phnd->vt[37];
                    pxf = ((XF *(*)(void *, int))e->fn)((char *)phnd + e->delta, 0);
                }
                M4 matA;
                func_0028F680(pxf, 0, &matA, 0, t);
                qword posT = QwTransformPosR(func_0011D558(matA, func_0011D768(*(M4 *)((char *)pxf + 0x40))), *(qword *)&vTarget);
                qword vel = func_00212628(JtXf(pjt)->pos, QwSub(posT, pjt->posHang.q), pjt->psophys->dvGravity.q, at[n - 1]);
                // The one register pin: a real TImode copy (movti -> qmtc2) of the call result into vf2. An asm
                // qmtc2 always issues a cycle early in sched2 (any dependence into an asm costs 1).
                register qword velT asm("vf2") = vel;
                float g = GLimitLm(&D_00341FF0, GEvalPoly(&D_003224E0, pjt->g1E58));
                JTAIR *pjtair = &pjt->jtair;
                UQ *pv = &pjt->jtair.v50;
                {
                    VTE *e = &pjt->vt[40];
                    ((void (*)(void *, qword))e->fn)((char *)pjt + e->delta, QwScaleX(velT, VU_FLOAT(g)));
                }
                func_001B7268(pjtair, 0xC, 0, 0, 1.0f);
                qword sub;
                OBJ *po = pjtair->p118;
                if (po) {
                    VTE *e = &po->vt[38];
                    qword q = pjt->jtair.q120;
                    sub = QwMul(q, ((qword (*)(void *))e->fn)((char *)po + e->delta));
                } else {
                    sub = D_00317560;
                }
                pv->q = QwSubJ(vel, sub);
                pjt->jtair.v50.f[2] = 0.0f;
            }
            break;
        case 24:
            if (!(pjt->pctl->held18 & func_00154798(pjt, 0x24)) && 0.5f < D_0036BB98 - pjt->tJts)
                func_001ADDD0(pjt, 0, -1);
            break;
        }
    } while (pjt->jts != jtsOld || pjt->jtbs != jtbsOld);
}

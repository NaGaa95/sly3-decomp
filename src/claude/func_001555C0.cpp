// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_00142AF8.cpp (Sly 3 offsets/addresses; the Sly 3 version has no D_003E1474 candidate loop).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct CLOCK { float t; float dt; };
struct LM { float gMin; float gMax; };
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; VTE e120; };
struct LO { char pad[0xC]; VT *pvt; };
struct R { char pad[0x40]; M3 m40; char pad1[0xA0 - 0x70]; void *pA0; };
struct Q { char pad[8]; R *p8; };
struct S;
struct P {
    char pad[0x50]; void *p60; char pad1[0xF64 - 0x54]; int nF04; char pad2[0x11B4 - 0xF68];
    S *ps10DC; int pad3; int n10E4; char pad4[0x11CC - 0x11C0]; Q *pq; LO *p10F8; int pad5;
    int n1100; int n1104; float g1110; float g1114; float g1118; int pad7;
    LM lmPan; LM lmTilt; float g1130; float g1134; char pad8[0x1218 - 0x1208]; int n1218; float g121C;
    M3 m1150;
};
struct GS { char pad[0x4E78]; int c4678; char pad1[0x4E90 - 0x4E7C]; S *ps4690; };
extern "C" {
extern CLOCK g_clock;
extern int D_00342DB8;
extern qword D_00317530;
extern GS D_00475480;
void func_00155328(P *p);
void func_00155270(P *p, int n, S *ps);
void func_00155380(P *p, S *ps, LO **ppv, float *pg, float *pg2);
void func_0012F3D0(Q *pq);
void func_0012F410(Q *pq);
qword func_001C9428(int n, P *p, qword q);
void func_00120528(qword v, float *pa, float *pb);
float func_0011EE98(LM *plm, float g);
M3 func_0011CAE0(float a, float b);
M3 func_0011C8C0(qword v, float g);
M3 func_0028EA00(void *pvFrom, void *pvTo, M3 *pm);
M3 func_0011C6F8(const M3 *pm);
qword func_0011D3C0(M3 *pm);
void func_0012F4F8(Q *pq, qword q);
void func_001555C0(P *p);
}
static inline qword Pos(LO *plo) { return plo->pvt->e120.pfn((char *)plo + plo->pvt->e120.d)->r[3]; }
struct VU_VECTOR4 { qword qw; };
inline M3 operator*(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.r[0];
    qword qwL1 = matL.r[1];
    qword qwL2 = matL.r[2];
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[0])->qw));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[1])->qw));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[2])->qw));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
static inline float GFrac(float g, float a, float b)
{
    if (b == a)
        return 0.5f;
    return (g - a) / (b - a);
}
static inline float X(const M3 &m, int i) { return ((float *)&m.r[0])[i]; }

void func_001555C0(P *p)
{
    int f;
    float pan, tilt;
    float g;
    if (p->pq == 0)
        return;
    f = 0;
    if (p->lmPan.gMin < p->lmPan.gMax || p->lmTilt.gMin < p->lmTilt.gMax)
        f = 1;
    if (p->nF04 != -1)
        f = 0;
    if (p->g121C < g_clock.t && (p->n1218 != 0 || f)) {
        p->n1218 = !p->n1218;
        func_00155328(p);
    }
    if (p->n1100 == 0) {
        if (D_00342DB8 != 0) {
            func_00155270(p, -1, 0);
        } else {
            S *psBest = p->ps10DC;
            int nBest = p->n10E4;
            float gBest;
            S *ps;
            if (psBest)
                func_00155380(p, psBest, &p->p10F8, &gBest, 0);
            else
                gBest = 3.402823466e+38f;
            if (D_00475480.c4678 > 0 && nBest < 3) {
                ps = D_00475480.ps4690;
                if (ps) {
                    float g3, g4;
                    func_00155380(p, ps, &p->p10F8, &g3, &g4);
                    if (nBest < 2 || (nBest == 2 && g3 < gBest)) {
                        psBest = ps;
                        nBest = 2;
                        gBest = g3;
                    }
                }
            }
            func_00155270(p, nBest, psBest);
        }
    }
    if (p->n1104 != 0) {
        func_0012F3D0(p->pq);
        pan = p->g1110;
        tilt = p->g1114;
        g = p->g1118;
    } else {
        if (p->p10F8 == 0 || p->n1218 == 0 || !f) {
            func_0012F410(p->pq);
            return;
        }
        func_0012F3D0(p->pq);
        func_00120528(func_001C9428(0, p, Pos(p->p10F8)), &pan, &tilt);
        pan = func_0011EE98(&p->lmPan, pan);
        tilt = func_0011EE98(&p->lmTilt, tilt);
        {
            float t;
            if (p->lmPan.gMax == p->lmPan.gMin)
                t = 0.5f;
            else
                t = (pan - p->lmPan.gMin) / (p->lmPan.gMax - p->lmPan.gMin);
            float u = t * __builtin_fabsf(t);
            g = (1.0f - u) * p->g1130 + u * p->g1134;
        }
    }
    M3 m0, m1;
    m0 = func_0011CAE0(pan, tilt) * func_0011C8C0(D_00317530, g);
    m1 = func_0028EA00(0, p->p60, &p->pq->p8->m40);
    m1 = m1 * func_0011C6F8(&p->m1150);
    M3 m2;
    if (X(m0, 0) + X(m1, 0) < 0.0f && X(m0, 1) * X(m1, 1) < 0.0f)
        m2 = p->m1150;
    else
        m2 = m0 * p->m1150;
    m2 = func_0028EA00(p->p60, p->pq->p8->pA0, &m2);
    func_0012F4F8(p->pq, func_0011D3C0(&m2));
}

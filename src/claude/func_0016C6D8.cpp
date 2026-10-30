// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0016C6D8: fixed camera matrix from p->p20 (same camera helpers as func_0016BFA8 / func_0016C280).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union M4 { struct { qword r[4]; } q; M3 m3; float af[4][4]; };
struct CLOCK { float t; float dt; };
extern "C" qword D_00317550;
union QF { float af[4]; qword q; };
static const QF s_vOff = { { -60.0f, -80.0f, 110.0f, 0.0f } };
struct SMP { float svFast; float svSlow; float dtFast; };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
struct CM : LO { char pad[0x118 - 0x10]; float g118; float g11C; char pad1[0x2F4 - 0x120]; int n2F4; };
struct Y { char pad[0x1CC]; float g1CC; char pad1[0x1E0 - 0x1D0]; LO *plo; int n1E4; };
struct X { CM *pcm; char pad[0x1C]; LO *p20; };
static inline M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
extern "C" {
void func_00169E78(X *p);
M3 func_0011CFC0(M4 *pm, M3 *pm2);
void func_0011D0B8(M3 *pm, float *pg, qword *pv);
float func_0011E598(float gCur, float gTarget, float dt, void *psmp, float *pdgNext); /* GSmooth */
M3 func_0011C8C0(qword v, float g);
qword *func_002BA818(qword *p, qword v);
void func_00166DE8(CM *p, M4 *m);
void func_00167960(CM *p, float g);
void func_0016C6D8(X *p);
qword func_001C9428(LO *plo, int n, qword q);
}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2];
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[0]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[1]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[2]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline float Length(qword a)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a), "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}

void func_0016C6D8(X *p)
{
    func_00169E78(p);
    qword pos = func_001C9428(p->p20, 0, s_vOff.q);
    M3 mRot = func_0011C8C0(D_00317550, 0.5f);
    M3 mNew = Mul(mRot, VMat(p->p20)->m3);
    M4 m4;
    M4 *pm4 = &m4;
    func_002BA818(&pm4->q.r[3], pos);
    pm4->q.r[0] = mNew.r[0];
    pm4->q.r[1] = mNew.r[1];
    pm4->q.r[2] = mNew.r[2];
    m4.af[2][3] = 0.0f;
    m4.af[1][3] = 0.0f;
    m4.af[0][3] = 0.0f;
    pm4->af[3][3] = 1.0f;
    func_00166DE8(p->pcm, pm4);
}

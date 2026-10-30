// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union M4 { struct { qword r[4]; } q; M3 m3; float af[4][4]; };
struct CLOCK { float t; float dt; };
extern "C" CLOCK D_0036BB98;
struct SMP { float svFast; float svSlow; float dtFast; };
static const SMP s_smp1 __attribute__((aligned(16))) = { 5.0f, 0.0f, 0.5f };
static const SMP s_smp2 __attribute__((aligned(16))) = { 2000.0f, 0.0f, 1.0f };
struct LO;
struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(LO *); };
struct LO { int a[3]; LOV *pvt; };
struct CM : LO { char pad[0x118 - 0x10]; float g118; float g11C; char pad1[0x2F4 - 0x120]; int n2F4; };
struct Y { char pad[0x1CC]; float g1CC; char pad1[0x1E0 - 0x1D0]; LO *plo; int n1E4; };
struct X { CM *pcm; char pad[0x1C]; Y *py; };
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
void func_0016BFA8(X *p);
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

void func_0016BFA8(X *p)
{
    func_00169E78(p);
    Y *py = p->py;
    M4 m = *VMat(py->plo);
    if (p->pcm->n2F4 == 0 && py->n1E4 != 0) {
        M3 mRel;
        M3 mNew;
        union { qword q; } axis;
        float rad;
        mRel = func_0011CFC0(&m, &VMat(p->pcm)->m3);
        func_0011D0B8(&mRel, &rad, &axis.q);
        if (rad < 0.0001f) {
            mNew = m.m3;
        } else {
            float g = func_0011E598(rad, 0.0f, D_0036BB98.dt, (void *)&s_smp1, 0);
            mNew = Mul(func_0011C8C0(axis.q, g), m.m3);
        }
        qword d = Sub(VMat(p->pcm)->q.r[3], m.q.r[3]);
        float dist = Length(d);
        qword pos;
        if (dist < 0.0001f)
            pos = m.q.r[3];
        else
            pos = AddScaled(m.q.r[3], d, VU_FLOAT(func_0011E598(dist, 0.0f, D_0036BB98.dt, (void *)&s_smp2, 0) / dist));
        func_002BA818(&m.q.r[3], pos);
        m.m3 = mNew;
        m.af[3][3] = 1.0f;
        m.af[2][3] = 0.0f;
        m.af[1][3] = 0.0f;
        m.af[0][3] = 0.0f;
    }
    func_00166DE8(p->pcm, &m);
    CM *pcm = p->pcm;
    if (pcm->g11C != pcm->g118)
        pcm->g11C = py->g1CC;
    else
        func_00167960(pcm, py->g1CC);
}

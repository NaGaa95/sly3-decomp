// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct CLQ { float g0, g1, g2; };
struct LM { float gMin, gMax; };
extern "C" CLQ D_00320F10, D_00320F30;
extern "C" LM D_00320F20, D_00320F40, D_00320F48, D_00320F50, D_00320F58;
struct CLOCK { float t; float dt; };
extern "C" CLOCK g_clock;
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct QVT { char pad[0x20]; short d4; short p4; int (*pfn4)(void *, int); short d5; short p5; int (*pfn5)(void *, int); };
struct Q { char pad[0xC]; float gC; float g10; float g14; char pad18[0x2C - 0x18]; QVT *pvt; };
struct T { char pad[0x20]; qword pos; };
struct W { char pad[0x50C]; int k50C; };
struct CM;
struct X {
    CM *pcm; char pad4[0x20 - 0x4]; W *pw; char *p24; T *pt; float t2C; U vTarget; U vVel;
};
extern "C" {
void func_00169E78(X *p);
Q *func_00169EB0(X *p);
int *func_001A7B20(int n);
float func_0011E940(float gLow, float gHigh);
void func_0012F4F8(T *pt, qword pos);
void func_00166DE8(CM *pcm, void *pm);
}
static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static inline void SetV(U *pv, float x, float y, float z) { pv->f[0] = x; pv->f[1] = y; pv->f[2] = z; }
static inline void SetV2(U *pv, float x, float y, float z) { pv->f[2] = z; pv->f[1] = y; pv->f[0] = x; }
static inline void SetV3(U *pv, float x, float y, float z) { pv->f[1] = y; pv->f[2] = z; pv->f[0] = x; }
static inline float GEval(const CLQ *pclq, float x) { return pclq->g0 + x * (pclq->g1 + x * pclq->g2); }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__ __volatile__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Zero() { qword q; __asm__ __volatile__("vsub.xyzw %0, $vf0, $vf0" : "=j"(q)); return q; }
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Sub(VU_VECTOR a, VU_VECTOR b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a.q), "j"(b.q)); return d; }
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
static inline qword AddScaled(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q));
    return r;
}
static inline qword AddScaled2(VU_VECTOR a, VU_VECTOR b, VU_VECTOR c, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %4x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(c.q), "j"(s.q));
    return r;
}
extern "C" void func_0016B298(X *p)
{
    qword pos, vel;
    func_00169E78(p);
    float gZero = 0.0f;
    Q *pq = func_00169EB0(p);
    if (gZero < pq->g14) {
        float sx = 1.0f;
        if (gZero < pq->gC)
            sx = -1.0f;
        float sy = 1.0f;
        if (gZero < pq->g10)
            sy = -1.0f;
        int *pf = func_001A7B20(1);
        int f = pf[0];
        if (pq->pvt->pfn4((char *)pq + pq->pvt->d4, 1))
            f = !f;
        if (f)
            sx = -sx;
        f = pf[1];
        if (pq->pvt->pfn5((char *)pq + pq->pvt->d5, 1))
            f = !f;
        if (f)
            sy = -sy;
        float gx = sx * GClamp(GEval(&D_00320F10, __builtin_fabsf(pq->gC)), D_00320F20.gMin, D_00320F20.gMax);
        float gy = sy * GClamp(GEval(&D_00320F30, __builtin_fabsf(pq->g10)), D_00320F40.gMin, D_00320F40.gMax);
        vel = Zero();
        union { qword q; } u;
        u.q = Make(0.0f, gy, gx);
        pos = u.q;
    } else if (p->pw->k50C != 9) {
        qword zero = Zero();
        pos = zero;
        vel = pos;
    } else {
        if (p->t2C < g_clock.t) {
            float y = func_0011E940(D_00320F48.gMin, D_00320F48.gMax);
            float z = func_0011E940(D_00320F50.gMin, D_00320F50.gMax);
            float *pv = p->vTarget.f;
            pv[0] = gZero;
            pv[1] = y;
            pv[2] = z;
            float t = g_clock.t;
            p->t2C = t + func_0011E940(D_00320F58.gMin, D_00320F58.gMax);
        }
        qword accel = VecCombo(VU_FLOAT(5.0f), Sub(p->vTarget.q, p->pt->pos), VU_FLOAT(-1.0f), p->vVel.q);
        vel = AddScaled(p->vVel.q, accel, VU_FLOAT(g_clock.dt));
        pos = AddScaled2(p->pt->pos, p->vVel.q, vel, VU_FLOAT(g_clock.dt * 0.5f));
    }
    func_0012F4F8(p->pt, pos);
    p->vVel.q = vel;
    func_00166DE8(p->pcm, p->p24 + 0x40);
}

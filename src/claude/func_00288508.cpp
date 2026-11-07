// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00288508: orbit-camera update (state 2: smooth to target angles; states 0/1: joystick pan/tilt rate, smoothed limits,
// clamp, integrate, aim the CM from the owner position + rotated (-50,0,0)). SMP aggregate inits give the memset libcall + temp copies.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct SMP { float g0, g4, g8; };
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct O { int a[3]; VTE *vt; char pad10[0x134 - 0x10]; void *x134; char pad138[0x1D8 - 0x138]; float x1D8, x1DC; };
struct CM;
struct P {
    CM *x0; char pad4[0x20 - 0x4]; int x20; int pad24; O *x28; float x2C, x30, x34, x38, x3C, x40, x44, x48, x4C, x50;
};
extern "C" {
extern struct CLOCK { float t; float dt; } g_clock;
void func_00169E78(P *p);
float func_0011E840(float gCur, float gTarget, float dt, const SMP *psmp, float *pdg);
M3 *func_0011CAE0(M3 *pm, float g1, float g2);
void func_00166E48(CM *p, qword pos, qword tgt, float da, float db);
void func_001A7B38(void *p, int n, float *pgPan, float *pgTilt);
float func_0011E3B8(float rad);
void func_00287000(O *p);
void func_00288508(P *p);
}
float GLimitAbs(float g, float gLimit);
float GSmooth(float gCur, float gTarget, float dt, SMP *psmp, float *pdgNext);
static const SMP RO_00329780 = { 1.0f, 0.0f, 0.2f };
static const struct { float x, y, z, w; } __attribute__((aligned(16))) RO_00329790 = { -50.0f, 0.0f, 0.0f, 0.0f };
static inline qword Pos(O *o) { VTE *v = &o->vt[36]; return *(qword *)((char *)v->pf((char *)o + v->d) + 0x30); }
static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z" : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Clamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static inline void Look(P *p, const M3 &m)
{
    qword v = MulM3(m, *(const qword *)&RO_00329790);
    qword pos = Add(Pos(p->x28), v);
    func_00166E48(p->x0, pos, Pos(p->x28), 0.0f, 0.0f);
}

extern "C" void func_00288508(P *p)
{
    func_00169E78(p);
    switch (p->x20) {
    case 2: {
        p->x2C = func_0011E840(p->x2C, p->x4C, g_clock.dt, &RO_00329780, 0);
        p->x30 = func_0011E840(p->x30, p->x50, g_clock.dt, &RO_00329780, 0);
        M3 m;
        func_0011CAE0(&m, p->x2C, p->x30);
        Look(p, m);
        break;
    }
    case 0:
    case 1: {
        float x, y;
        float gRate = 10.0f;
        func_001A7B38(p->x28->x134, 2, &x, &y);
        float gT = 0.2f;
        x = p->x34 + GLimitAbs(x - p->x34, g_clock.dt * gRate);
        y = p->x38 + GLimitAbs(y - p->x38, g_clock.dt * gRate);
        SMP smpPan = { p->x28->x1D8, 0.0f, gT };
        SMP smpTilt = { p->x28->x1DC, 0.0f, gT };
        float dt = g_clock.dt * 0.5f;
        float gMin, gMax;
        GSmooth(p->x2C, p->x3C, dt, &smpPan, &gMin);
        GSmooth(p->x2C, p->x40, dt, &smpPan, &gMax);
        p->x34 = Clamp(x, gMin, gMax);
        GSmooth(p->x30, p->x44, dt, &smpTilt, &gMin);
        GSmooth(p->x30, p->x48, dt, &smpTilt, &gMax);
        p->x38 = Clamp(y, gMin, gMax);
        p->x2C += p->x34 * g_clock.dt;
        p->x30 += p->x38 * g_clock.dt;
        if (6.2831855f <= p->x40 - p->x3C)
            p->x2C = func_0011E3B8(p->x2C);
        M3 m;
        func_0011CAE0(&m, p->x2C, p->x30);
        Look(p, m);
        if (p->x20 == 0) {
            VTE *e = &p->x28->vt[35];
            e->pf((char *)p->x28 + e->d, &m);
            func_00287000(p->x28);
        }
        break;
    }
    }
}

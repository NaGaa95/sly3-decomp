// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Steers the actor's velocity for one frame: drag along its forward axis, damping across it, a yaw turn about
// the up axis, then two velocity corrections handed to func_00244828 (sideways clamped to `limit`, and forward).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union UQ { qword q; float f[4]; };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
struct VU_FLOATM {
    qword q;
    VU_FLOATM(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "rV"(*(int *)&f)); }
};
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Dot(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
        : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline qword Scale(qword v, qword f)
{
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f), "j"(v));
    return r;
}
static inline qword Scale(qword v, VU_FLOAT f)
{
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(v));
    return r;
}
static inline qword DivF(qword v, VU_FLOATM f)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(f.q));
    return r;
}
static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v));
    return r;
}
static inline float GetXM(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q));
    return f;
}
static inline float GetZ(qword q)
{
    float f;
    __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q));
    return f;
}

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct BASE { int x0, x4, x8; };
struct M4 { qword r[4]; };
struct P : BASE {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h)
    virtual void i2(); virtual void i3(); virtual void i4();
    virtual M4 *GetMatrix();           /* 0x120 */
    virtual void i1();
    virtual qword GetVel();            /* 0x130 */
    virtual qword GetAngVel();         /* 0x138 */
};
struct CLOCK { float t; float dt; };
extern "C" {
extern CLOCK D_0036BB98;
extern qword D_00317550;
float func_0011FE60(qword a, qword b, qword *ppar, qword *pperp);
float func_0011E560(float g, float gMax);
M3 func_0011C8C0(qword axis, float g);
qword func_001205F0(qword v, float g);
void func_00244828(P *p, qword v);
}

extern "C" void func_001B0228(P *p, float drag, float damping, float limit)
{
    qword vel = p->GetVel();
    qword w = p->GetAngVel();
    UQ par, perp;
    M3 mat = *(M3 *)p->GetMatrix();
    M3 mc;
    float dot = func_0011FE60(vel, mat.r[0], &par.q, &perp.q);
    float dt = D_0036BB98.dt;
    float turn = GetZ(w) * dt;
    par.q = Scale(mat.r[0], VU_FLOAT(dot - drag * dt));
    perp.q = Scale(perp.q, VU_FLOAT(1.0f - damping * dt));
    M3 m = func_0011C8C0(D_00317550, turn);
    mc = m;
    qword t = MulM3(mc, Add(par.q, perp.q));
    qword acc = DivF(Sub(t, vel), VU_FLOATM(D_0036BB98.dt));
    qword side = Sub(acc, Scale(D_00317550, Dot(acc, D_00317550)));
    func_00244828(p, func_001205F0(side, limit));
    float along = GetXM(Dot(t, mat.r[0]));
    float g = func_0011E560((1400.0f - along) / D_0036BB98.dt, 1500.0f);
    func_00244828(p, Scale(mat.r[0], VU_FLOAT(g)));
}

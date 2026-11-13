// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001B88E0: per-frame body motion update by mode (Sly 2 func_00196DF8 relative).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U row[3]; };
struct M4 { U row[4]; };
struct VTE { short delta, pad; void *fn; };
struct BODY { char pad0[0xB0]; U angularVelocity; char padC0[0x30]; U angularAcceleration; };
struct ACTOR { char pad0[12]; VTE *vt; char pad10[0x3C]; BODY *body; };
struct CONTEXT {
    ACTOR *actor; int state; char pad8[0x10]; float stamp; int mode; float x20; char pad24[0xC]; float gain; char pad34[0x1C];
    U desired; char pad60[0xB8]; ACTOR *rider; U riderScale; char pad130[0x58]; float targetX, targetZ;
};
struct CLOCK { float time, dt; };
struct SMP { float maximum, minimum, duration; };
struct RANGE { float low, high; };
struct POLY { float c0, c1, c2; };

extern "C" {
extern CLOCK g_clock;
extern ACTOR *D_0036B250;
extern U D_00317530, D_00317550, D_00317560;
extern SMP D_00323030, D_00323040, D_00323050;
extern POLY D_00323060;
extern RANGE D_00341FF0;
qword func_001C94E8(void *, ACTOR *, qword);
M3 *func_0011C930(M3 *, qword);
M3 *func_0011CBA0(M3 *, qword);
float func_0011E598(float, float, float, SMP *, float *);
qword func_001205F0(qword, float);
void func_00244828(ACTOR *, qword);
void func_001B8570(CONTEXT *, U *);
}

static inline qword Scalar(float f) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); return q; }
static inline qword ScalarW(const float &f) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "rV"(*(const int *)&f)); return q; }
static inline qword Velocity(ACTOR *p) { VTE &v = p->vt[38]; return ((qword (*)(void *))v.fn)((char *)p + v.delta); }
static inline M4 *Matrix(ACTOR *p) { VTE &v = p->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.delta); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Mul(qword a, qword b) { qword r; __asm__("vmul.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Scale(qword v, qword f) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(f)); return r; }
static inline qword AddScaled(qword a, qword b, qword g)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(g));
    return r;
}
static inline qword DivF(qword v, qword f)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(f));
    return r;
}
static inline qword Rotate(qword r0, qword r1, qword r2, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r) : "j"(r0), "j"(r1), "j"(r2), "j"(v));
    return r;
}
static inline qword Rotate(const M3 &m, qword v) { return Rotate(m.row[0].q, m.row[1].q, m.row[2].q, v); }
static inline qword RotateC(qword r0, qword r1, qword r2, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r) : "j"(r0), "j"(r1), "j"(r2), "j"(v));
    return r;
}
static inline qword RotateF(qword r0, qword r1, qword r2, qword v)
{
    qword r = v;
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(r) : "j"(r0), "j"(r1), "j"(r2));
    return r;
}
static inline qword RotateF(const M3 &m, qword v) { return RotateF(m.row[0].q, m.row[1].q, m.row[2].q, v); }
static inline float GetXM(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword ToVf(qword v) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(v)); return r; }
static inline float GetZ(qword q) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(q)); return f; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Sqrt(qword d) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=&j"(r) : "j"(d)); return r; }
static inline qword Unit(qword v, qword l)
{
    qword r;
    __asm__ __volatile__("vdiv $Q,$vf0w,%0x\n\tvwaitq" : : "j"(l));
    __asm__("vmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v));
    return r;
}
// M * v with rows dotted by v, w from v
static inline qword MulM3(const M3 &m, qword v)
{
    qword r = v;
    qword t0, t1, t2, one;
    __asm__("vmul.xyzw %2,%5,%0\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%0\n\tvmul.xyzw %4,%7,%0\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "+j"(r), "=&j"(one), "=&j"(t0), "=&j"(t1), "=&j"(t2) : "j"(m.row[0].q), "j"(m.row[1].q), "j"(m.row[2].q));
    return r;
}
static inline float GClamp(float g, float lo, float hi) { if (g < lo) return lo; else if (hi < g) return hi; else return g; }

static inline qword AngularStep(qword a, qword b, qword g, BODY *body)
{
    qword r;
    // Keep the body pointer live through the VU step so its load precedes the half-step constant.
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(g), "r"(body));
    return r;
}

extern "C" void func_001B88E0(CONTEXT *p)
{
    switch (p->mode) {
    case 21: {
        U local;
        U scalar;
        M3 basis, rotation, returned;
        qword original = Velocity(p->actor);
        local.q = func_001C94E8(0, p->actor, original);
        BODY *body = p->actor->body;
        qword av = body->angularVelocity.q;
        scalar.q = Scalar(g_clock.dt);
        qword step = AngularStep(av, body->angularAcceleration.q, scalar.q, body);
        scalar.q = Scalar(g_clock.dt * 0.5f);
        func_0011C930(&rotation, Scale(Add(body->angularVelocity.q, step), scalar.q));
        M4 *m = Matrix(p->actor);
        M3 *mp = (M3 *)m;
        qword r0, r1, r2;
        r0 = RotateC(rotation.row[0].q, rotation.row[1].q, rotation.row[2].q, mp->row[0].q);
        basis.row[0].q = r0;
        r1 = RotateC(rotation.row[0].q, rotation.row[1].q, rotation.row[2].q, mp->row[1].q);
        // Preserve the store order so the first smoothing call's timestep load can issue before both stores.
        *(volatile qword *)&basis.row[1].q = r1;
        *(volatile qword *)&returned.row[0].q = r0;
        r2 = RotateC(rotation.row[0].q, rotation.row[1].q, rotation.row[2].q, mp->row[2].q);
        returned.row[1].q = r1;
        returned.row[2].q = r2;
        basis.row[2].q = r2;
        local.f[0] = func_0011E598(local.f[0], p->targetX, g_clock.dt, &D_00323030, 0);
        local.f[1] = func_0011E598(local.f[1], 0.0f, g_clock.dt, &D_00323040, 0);
        local.f[2] = func_0011E598(local.f[2], p->targetZ, g_clock.dt, &D_00323050, 0);
        scalar.q = ScalarW(g_clock.dt);
        qword accel = DivF(Sub(RotateF(basis, local.q), original), scalar.q);
        func_00244828(p->actor, func_001205F0(accel, 8000.0f));
        break;
    }
    case 8: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 22:
        break;
    default: {
        U direction;
        M3 basis;
        qword velocity = Velocity(p->actor);
        U *pd = &direction;
        qword other;
        if (p->rider) {
            qword scale = p->riderScale.q;
            other = Mul(scale, Velocity(p->rider));
        } else
            other = D_00317560.q;
        pd->q = Sub(velocity, other);
        direction.i[2] = 0;
        const U *fallback = &D_00317530;
        qword v = ToVf(direction.q);
        // The original keeps the normalization length in vf2 across the fallback branch.
        register qword len __asm__("vf2") = Sqrt(Dot(v, v));
        if (GetXM(len) < 0.0001f)
            direction = *fallback;
        else
            direction.q = Unit(v, len);
        float speed = GetXM(len);
        {
            M3 returned;
            func_0011CBA0(&returned, direction.q);
            basis = returned;
        }
        U local, accel, corrected, scalar;
        local.q = MulM3(basis, p->desired.q);
        float inv = 1.0f / g_clock.dt;
        float side, longitudinal;
        if (p->mode == 0 || p->mode == 2) {
            side = inv;
            longitudinal = side;
        } else {
            longitudinal = local.f[0] < speed ? 3.5f : 2.5f;
            side = 2.5f;
        }
        accel.f[0] = longitudinal * (local.f[0] - speed);
        accel.f[1] = side * local.f[1];
        accel.i[2] = 0;
        float gain;
        if (p->state == 12) {
            float t = g_clock.time - p->stamp;
            gain = GClamp(D_00323060.c0 + t * (D_00323060.c1 + t * D_00323060.c2), D_00341FF0.low, D_00341FF0.high);
        } else
            gain = p->gain;
        scalar.q = Scalar(gain);
        accel.q = Scale(accel.q, scalar.q);
        corrected.q = Rotate(basis, accel.q);
        func_001B8570(p, &corrected);
        if (p->actor == D_0036B250) {
            float vz = GetZ(velocity);
            if (vz < 0.0f && (p->mode == 4 || (p->mode == 5 && g_clock.time - p->x20 < 0.2f)))
                {
                    scalar.q = Scalar((500.0f - vz) * 1.5f);
                    corrected.q = AddScaled(corrected.q, D_00317550.q, scalar.q);
                }
        }
        if (p->mode != 7) {
            float vz = GetZ(velocity);
            if (vz < -750.0f)
                {
                scalar.q = Scalar((vz - -750.0f) * -2.0f);
                corrected.q = AddScaled(corrected.q, D_00317550.q, scalar.q);
            }
        }
        func_00244828(p->actor, corrected.q);
        break;
    }
    }
}

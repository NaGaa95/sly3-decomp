// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// func_0027ADC8: vehicle forces (Sly 2 VehicleForces__FP3ALO 0x1D2E18, src/hand/func_001D2E18.cpp in the Sly 2 decomp):
// four wheel contacts (entries 0x190, stride 0x60) push the body and accumulate the two traction slips, then turn and drive
// the body within the remaining impulse budget; Sly 3 adds an optional tilt toward the wheel plane (+0x370).
// Keys: the wheel-frame and tilt matrices come from by-value M3 returns (BuildRotateMatrixAxis 0x11C8C0, 0x11C930) fed
// straight into an NRV product whose row temporaries are memory structs (MulV) - that gives the target's slot layout and
// per-row double stores; the phase rotation uses the same callee through its out-pointer form (asm-label binding).
// Dot's mtc1 carries two allocation-only "j" operands; the tangent scale takes the dot first (ScaleR).
typedef int qword __attribute__((mode(TI)));
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
union U { qword q; float f[4]; unsigned int bits[4]; };
struct M3 { U rows[3]; };
struct MOTION { M3 local; char pad30[0x10]; M3 world; char pad70[0x30]; MOTION *space; char padA4[0xC]; U velocity; char padC0[0x30]; U acceleration; };
struct PHYSICS { char pad0[0x28]; float inertia; char pad2C[0x5C]; float gravity; char pad8C[0x44]; float mass; };
struct CONTACT { char pad0[0x10]; U point; char pad20[0x24]; MOTION *motion; char pad48[0x38]; U normal; float depth; };
struct ENTRY { char pad0[0x8]; float angle; char padC[0xC]; float minimum, maximum, x; char pad24[0x3C]; };
struct POLY { float a, b, c; };
struct LIMITS { float low, high; };
struct VTE { short delta, pad; M3 *(*pfn)(void *); };
struct HOLDER { char pad0[0xA0]; MOTION *xf; };
struct TILT { char pad0[0x20]; qword q; };
struct P {
    char pad0[0xC]; VTE *vt; char pad10[0x38]; MOTION *primary, *secondary, *space; char pad54[0x84]; PHYSICS *physics;
    char padDC[0xB4]; ENTRY entries[4]; POLY traction; int unused31C; LIMITS limits; float reverseLimit, slip; char pad330[0x8];
    float contactScale, drive, turnScale; char pad344[0x28]; HOLDER *holder; TILT *tilt; char pad374[0xC]; M3 matTilt;
    char pad3B0[0x58]; float f408, slipSide, slipFwd, f414;
};
struct CLOCK { float time, dt; };
union PHASE { M3 rotation; struct { U world, limited, dtv; } impulse; };
extern CLOCK g_clock;
extern const qword D_00317550;
extern const POLY D_003293B0, D_003293C0;
extern "C" {
void func_00243738(P *);
CONTACT *func_0027AD80(P *, ENTRY *);
qword func_0028BCD0(MOTION *, MOTION *, qword);
void func_00244770(P *, qword, qword);
M3 func_0011C8C0(qword, float);
void func_0011C8C0p(M3 *, qword, float) asm("func_0011C8C0");   /* same function, out-pointer form */
qword func_0028E990(MOTION *, MOTION *, qword);
float GLimitAbs__Fff(float, float);
void func_00244890(P *, qword);
qword func_001205F0(qword, float);
void func_00244828(P *, qword);
M3 func_0011C930(qword);
qword func_0011D3C0(M3 *);
}
static inline M3 *GetMatrix(P *p) { return p->vt[36].pfn((char *)p + p->vt[36].delta); }
static inline VV ScalarBits(int b) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "rV"(b)); return r; }
static inline VV TimeStep(const CLOCK &c) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "rV"(*(const int *)&c.dt)); return r; }
static inline VV Scalar(float f) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline VV Subtract(VV a, VV b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline VV Scale(VV a, VV b) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline VV ScaleR(VV s, VV a) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(s), "j"(a)); return r; }
static inline VV AddScaled(qword origin, qword axis, qword amount)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(origin), "j"(axis), "j"(amount));
    return r;
}
static inline float Dot(VV a, VV b)
{
    qword r, one;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(r), "j"(r), "j"(r));
    return f;
}
static inline VV DotV(VV a, VV b)
{
    qword r, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline VV Rotate(const M3 &m, VV v)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(v) : "j"(m.rows[0].q), "j"(m.rows[1].q), "j"(m.rows[2].q));
    return v;
}
static inline VV InverseRotate(const M3 &m, VV v)
{
    qword r = m.rows[0].q, one, d0, d1, d2;
    __asm__("vmul.xyzw %1,%4,%5\n\tvmaxw.xyzw %0,$vf0,$vf0w\n\tvmul.xyzw %2,%6,%5\n\tvmul.xyzw %3,%7,%5\n\t"
            "vadday.x $ACC,%1,%1y\n\tvmaddz.x %4,%0,%1z\n\tvaddax.y $ACC,%2,%2x\n\tvmaddz.y %4,%0,%2z\n\t"
            "vaddax.z $ACC,%3,%3x\n\tvmaddy.z %4,%0,%3y"
            : "=&j"(one), "=&j"(d0), "=&j"(d1), "=&j"(d2), "+j"(r) : "j"(v), "j"(m.rows[1].q), "j"(m.rows[2].q));
    return r;
}
static inline VV Divide(VV v, VV scalar) { qword r; __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(scalar), "j"(v)); return r; }
static inline VV Cross(VV a, VV b) { qword r; __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
struct VU_VECTOR4 { qword qw; };
inline M3 MulV(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.rows[0].q;
    qword qwL1 = matL.rows[1].q;
    qword qwL2 = matL.rows[2].q;
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.rows[0])->qw));
    *(VU_VECTOR4 *)&mat.rows[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.rows[1])->qw));
    *(VU_VECTOR4 *)&mat.rows[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.rows[2])->qw));
    *(VU_VECTOR4 *)&mat.rows[2] = v2;
}
static inline float Evaluate(const POLY &p, float t) { return p.a + t * (p.b + t * p.c); }
static inline float Clamp(float v, float low, float high) { if (v < low) return low; else if (high < v) return high; else return v; }
static inline float ClampTo(float v, const LIMITS &l) { return Clamp(v, l.low, l.high); }
static inline float Min(float a, float b) { return b < a ? b : a; }
static inline float Abs(float f) { return __builtin_fabsf(f); }

extern "C" void func_0027ADC8(P *p)
{
    func_00243738(p);
    float total = 0.0f;
    M3 basis = *GetMatrix(p);
    VV normal = basis.rows[2].q;
    U scalar;
    p->slipSide = 0.0f;
    p->slipFwd = 0.0f;
    for (unsigned int i = 0; i < 4; i++) {
        ENTRY *entry = &p->entries[i];
        CONTACT *hit = func_0027AD80(p, entry);
        if (hit) {
            qword point = hit->point.q;
            qword previous = func_0028BCD0(p->space, 0, point);
            VV other = func_0028BCD0(hit->motion, 0, point);
            float ratio = hit->depth / (entry->maximum - entry->minimum);
            float fraction = Clamp(ratio, 0.0f, 1.0f);
            float velocityCurve = Evaluate(D_003293B0, fraction);
            float depthCurve = Evaluate(D_003293C0, fraction);
            VV dv = Subtract(other, previous);
            float response = Dot(dv, normal) * velocityCurve * 15.0f + hit->depth * depthCurve * 90.0f;
            if (response < 0.0f)
                continue;
            response *= p->physics->mass;
            total += response;
            scalar.q = Scalar(response);
            qword force = Scale(normal, scalar.q);
            func_00244770(p, point, force);
            VV n = hit->normal.q;
            VV tangent = Subtract(dv, ScaleR(DotV(dv, n), n));
            M3 m = MulV(basis, func_0011C8C0(D_00317550, entry->angle));
            float gSide = Abs(Dot(tangent, m.rows[0].q));
            float gFwd = Abs(Dot(tangent, m.rows[1].q));
            p->slipFwd += response * gFwd / p->f414;
            p->slipSide += response * gSide / p->slip;
        }
    }
    if (0.0f < total) {
        p->slipFwd /= total;
        p->slipSide /= total;
    }
    CLOCK *clock = &g_clock;
    p->f408 = total / (p->physics->mass * -p->physics->gravity);
    float budget = Min(11250.0f, p->contactScale * total / p->physics->mass);
    U velocity, localVelocity, torque, worldTorque;
    M3 basis2;
    U desired, acceleration;
    PHASE phase;
    qword origin = p->primary->velocity.q;
    velocity.q = ScalarBits(*(const int *)&clock->dt);
    scalar.q = AddScaled(origin, p->primary->acceleration.q, velocity.q);
    velocity.q = func_0028E990(p->primary->space, p->secondary, scalar.q);
    localVelocity.q = InverseRotate(p->secondary->local, p->secondary->velocity.q);
    float width = p->entries[0].x - p->entries[2].x;
    float turn = Min(velocity.f[0], 1000.0f) * p->turnScale / width;
    float quarter = width * 0.25f;
    float accel = p->physics->mass * quarter / p->physics->inertia;
    torque.f[0] = torque.f[1] = 0.0f;
    float turnImpulse = GLimitAbs__Fff((turn - localVelocity.f[2]) / clock->dt, accel * budget);
    torque.f[2] = turnImpulse;
    worldTorque.q = Rotate(p->secondary->world, torque.q);
    budget -= Abs(turnImpulse * 0.5f / accel);
    func_00244890(p, worldTorque.q);
    float dt = clock->dt;
    float half = dt * 0.5f;
    func_0011C8C0p(&phase.rotation, D_00317550, (localVelocity.f[2] + torque.f[2] * half) * dt);
    desired.f[0] = p->drive;
    desired.f[2] = desired.f[1] = 0.0f;
    basis2 = phase.rotation;
    desired.q = Rotate(basis2, desired.q);
    float fraction = velocity.f[0] / p->slip;
    float minimum, maximum;
    if (0.0f <= p->drive) {
        minimum = -p->reverseLimit;
        maximum = ClampTo(Evaluate(p->traction, Clamp(fraction, 0.0f, 1.0f)), p->limits);
    } else {
        minimum = -ClampTo(Evaluate(p->traction, Clamp(-fraction, 0.0f, 1.0f)), p->limits);
        maximum = p->reverseLimit;
    }
    phase.impulse.dtv.q = TimeStep(g_clock);
    acceleration.q = Divide(Subtract(desired.q, velocity.q), phase.impulse.dtv.q);
    acceleration.bits[2] = 0;
    acceleration.f[0] = Clamp(acceleration.f[0], minimum, maximum);
    phase.impulse.limited.q = func_001205F0(acceleration.q, budget);
    phase.impulse.world.q = func_0028E990(p->secondary, 0, phase.impulse.limited.q);
    func_00244828(p, phase.impulse.world.q);
    if (p->tilt) {
        phase.impulse.dtv.q = Scalar(3.0e-5f);
        qword v = func_001205F0(Scale(Cross(phase.impulse.world.q, D_00317550), phase.impulse.dtv.q), 0.075f);
        v = func_0028E990(0, p->holder->xf, v);
        M3 m;
        m = MulV(func_0011C930(v), p->matTilt);
        TILT *ptilt = p->tilt;
        ptilt->q = func_0011D3C0(&m);
    }
}

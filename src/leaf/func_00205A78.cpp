// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Vehicle contact/traction update (Sly 3 form of the Sly 2 wheel controller func_001D2E18): realign the body to the ground
// when requested, push the body with the impulses of the four wheel contacts, then turn and drive it within the remaining
// impulse budget, and finally steer the follow target's orientation from the applied impulse.
// Matching notes: the phase union shares the rotation and the three impulse vectors; `dtv` also holds the small steering
// scale; `product` is declared with the other function-wide locals; MulMat keeps both the output and a dead local copy.
typedef int qword __attribute__((mode(TI)));
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
union U { qword q; float f[4]; unsigned int bits[4]; };
struct M3 { U rows[3]; };
struct M4 { M3 basis; U position; };
struct MOTION { M4 local, world; char pad80[0x20]; MOTION *space; char padA4[0xC]; U velocity; char padC0[0x30]; U acceleration; };
struct PHYSICS { char pad0[0x28]; float inertia; char pad2C[0xA4]; float mass; };
struct CONTACT { char pad0[0x10]; U point; char pad20[0x24]; MOTION *motion; char pad48[0x48]; float depth; char pad94[0x18]; CONTACT *next; };
struct ENTRY { int active; CONTACT *contacts; char pad8[0xC]; float radius; float minimum, maximum; U point; char pad30[0x30]; };
struct POLY { float a, b, c; };
struct LIMITS { float low, high; };
struct VTE { short delta, pad; void *fn; };
struct TARGET { char pad0[0x20]; U orientation; };
struct P {
    char pad0[0xC]; VTE *vt; char pad10[0x48 - 0x10]; MOTION *primary, *secondary, *space; char pad54[0xD8 - 0x54]; PHYSICS *physics;
    char padDC[0x190 - 0xDC]; ENTRY entries[4];
    POLY traction; int pad31C; LIMITS limits; float reverseLimit, slip; char pad330[8]; float contactScale, drive, turnScale;
    char pad344[4]; MOTION *follow; TARGET *target; M3 reference;
    int state; char pad384[0x428 - 0x384]; int x428; POLY x42C;
};
struct CLOCK { float time, dt; };
extern CLOCK D_0036BB98;
extern const qword D_00317550;
extern POLY D_00325790, D_003257A0;
extern "C" {
void func_00243738(P *);
int func_002058D8(P *);
void func_0011CCF8(M4 *, M3 *, M3 *);
void func_0023EDE8(P *, M3 *, M3 *);
void *func_00205840(P *, ENTRY *);
qword func_0028BCD0(MOTION *, MOTION *, qword);
void func_00244770(P *, qword, qword);
float func_0011E560(float, float);
void func_00244890(P *, qword);
M3 *func_0011C8C0(M3 *, qword, float);
qword func_001205F0(qword, float);
qword func_0028E990(MOTION *, MOTION *, qword);
void func_00244828(P *, qword);
void func_0011C930(M3 *, qword);
qword func_0011D3C0(M3 m);
}
static inline VV ScalarBits(int b) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "rV"(b)); return r; }
static inline VV TimeStep(const CLOCK &c) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "rV"(*(const int *)&c.dt)); return r; }
static inline VV Scalar(float f) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline VV Subtract(VV a, VV b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline VV Scale(VV a, VV b) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(b)); return r; }
// origin + axis * amount.x
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
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(r));
    return f;
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
static inline float Evaluate(const POLY &p, float t) { return p.a + t * (p.b + t * p.c); }
static inline float Clamp(float v, float low, float high) { if (v < low) return low; else if (high < v) return high; else return v; }
static inline float ClampTo(float v, const LIMITS &l) { return Clamp(v, l.low, l.high); }
static inline float Min(float a, float b) { return b < a ? b : a; }
static inline float Abs(float f) { return __builtin_fabsf(f); }
static inline M4 *PlacementOf(P *p)
{
    VTE *e = &p->vt[36];
    return ((M4 *(*)(void *))e->fn)((char *)p + e->delta);
}

static inline VV Cross(VV a, VV b) { qword r; __asm__("vopmula.xyz $ACC,%1,%2
	vopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulRow(const M3 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x
	vmadday.xyz $ACC,%2,%4y
	vmaddz.xyz %0,%3,%4z"
            : "=j"(r) : "j"(m->rows[0].q), "j"(m->rows[1].q), "j"(m->rows[2].q), "j"(v));
    return r;
}
struct Q3 { qword r[3]; };
static inline void MulMat(Q3 *pr, const M3 *a, const M3 *b)
{
    Q3 r;
    register qword first __asm__("vf4"); /* pin: first row in vf4 (otherwise vf4/vf5 are swapped with the third matrix row) */
    qword t0;
    first = b->rows[0].q;
    __asm__("vmulax.xyz $ACC,%1,%4x
	vmadday.xyz $ACC,%2,%4y
	vmaddz.xyz %0,%3,%4z"
            : "=j"(t0) : "j"(a->rows[0].q), "j"(a->rows[1].q), "j"(a->rows[2].q), "j"(first));
    r.r[0] = pr->r[0] = t0;
    r.r[1] = pr->r[1] = MulRow(a, b->rows[1].q);
    pr->r[2] = r.r[2] = MulRow(a, b->rows[2].q);
}
extern "C" void func_00205A78(P *p)
{
    if (p->state == 4)
        return;
    func_00243738(p);
    if (p->x428) {
        if (func_002058D8(p)) {
            M3 reset;
            func_0011CCF8(PlacementOf(p), 0, &reset);
            func_0023EDE8(p, &reset, (M3 *)&p->x42C);
        }
    }
    U scalar, velocity, localVelocity, torque, worldTorque;
    M3 basis;
    U desired;
    union PHASE { M3 rotation; struct { U acceleration, world, limited; } impulse; } phase;
    U dtv;
    M3 product;
    float total = 0.0f;
    for (unsigned int i = 0; i < 4; i++) {
        ENTRY *entry = &p->entries[i];
        CONTACT *hit = (CONTACT *)func_00205840(p, entry);
        if (hit) {
            qword point = hit->point.q;
            VV normal = PlacementOf(p)->basis.rows[2].q;
            qword previous = func_0028BCD0(p->space, 0, point);
            VV other = func_0028BCD0(hit->motion, 0, point);
            float ratio = hit->depth / (entry->maximum - entry->minimum);
            float fraction = Clamp(ratio, 0.0f, 1.0f);
            float velocityCurve = Evaluate(D_00325790, fraction);
            float depthCurve = Evaluate(D_003257A0, fraction);
            float response = Dot(Subtract(other, previous), normal) * velocityCurve * 15.0f + hit->depth * depthCurve * 90.0f;
            if (response <= 0.0f) continue;
            if (3600.0f < response) response = 3600.0f;
            scalar.q = Scalar(response * p->physics->mass);
            qword force = Scale(normal, scalar.q);
            func_00244770(p, point, force);
            total += Dot(force, normal);
        }
    }
    float budget = Min(11250.0f, p->contactScale * total / p->physics->mass);
    CLOCK *clock = &D_0036BB98;
    qword origin = p->primary->velocity.q;
    velocity.q = ScalarBits(*(const int *)&clock->dt);
    scalar.q = AddScaled(origin, p->primary->acceleration.q, velocity.q);
    velocity.q = func_0028E990(p->primary->space, p->secondary, scalar.q);
    localVelocity.q = InverseRotate(p->secondary->local.basis, p->secondary->velocity.q);
    float width = p->entries[0].point.f[0] - p->entries[2].point.f[0];
    float turn = Min(velocity.f[0], 1000.0f) * p->turnScale / width;
    float acceleration = 2.0f * p->physics->mass * width / p->physics->inertia;
    torque.f[0] = torque.f[1] = 0.0f;
    float turnImpulse = func_0011E560((turn - localVelocity.f[2]) / clock->dt, acceleration * budget);
    torque.f[2] = turnImpulse;
    worldTorque.q = Rotate(p->secondary->world.basis, torque.q);
    budget -= Abs(0.2f * turnImpulse / acceleration);
    func_00244890(p, worldTorque.q);
    float dt = clock->dt;
    float half = dt * 0.5f;
    func_0011C8C0(&phase.rotation, D_00317550, (localVelocity.f[2] + torque.f[2] * half) * dt);
    desired.f[0] = p->drive;
    desired.f[2] = desired.f[1] = 0.0f;
    basis = phase.rotation;
    desired.q = Rotate(basis, desired.q);
    float fraction = velocity.f[0] / p->slip;
    float minimum, maximum;
    if (0.0f <= p->drive) {
        minimum = -p->reverseLimit;
        maximum = ClampTo(Evaluate(p->traction, Clamp(fraction, 0.0f, 1.0f)), p->limits);
    } else {
        minimum = -ClampTo(Evaluate(p->traction, Clamp(-fraction, 0.0f, 1.0f)), p->limits);
        maximum = p->reverseLimit;
    }
    dtv.q = TimeStep(D_0036BB98);
    phase.impulse.acceleration.q = Divide(Subtract(desired.q, velocity.q), dtv.q);
    phase.impulse.acceleration.bits[2] = 0;
    phase.impulse.acceleration.f[0] = Clamp(phase.impulse.acceleration.f[0], minimum, maximum);
    phase.impulse.limited.q = func_001205F0(phase.impulse.acceleration.q, budget);
    phase.impulse.world.q = func_0028E990(p->secondary, 0, phase.impulse.limited.q);
    func_00244828(p, phase.impulse.world.q);
    if (p->target) {
        VV cross = Cross(phase.impulse.world.q, D_00317550);
        dtv.q = Scalar(3.0e-5f);
        qword steer = func_001205F0(Scale(cross, dtv.q), 0.075f);
        qword local = func_0028E990(0, p->follow->space, steer);
        Q3 t;
        M3 axis;
        func_0011C930(&axis, local);
        TARGET *target = p->target;
        MulMat(&t, &axis, &p->reference);
        product = *(M3 *)&t;
        target->orientation.q = func_0011D3C0(product);
    }
}

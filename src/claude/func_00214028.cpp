// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -malign-loops=3
// Vehicle drive update (sibling of the wheel controller func_00205A78; states 2, 4 and 5 only): yaw the body toward the
// commanded turn rate, push it toward the commanded drive speed within the optional acceleration limit, then ease the
// body's height to its hover target (plus the lift offset in states 5/6) through func_00120C80 and push vertically.
// Matching notes: the phase union shares the rotation with the impulse vectors; the clock pointer is used up to the first
// TimeStep and the global directly afterwards (gives the s0 reuse and the later recomputed address); `origin` is read
// after the basis copy; each by-value VU float has its own U local for the home store; Z() is the pextuw lane read.
typedef int qword __attribute__((mode(TI)));
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
union U { qword q; float f[4]; unsigned int bits[4]; };
struct M3 { U rows[3]; };
struct M4 { M3 basis; U position; };
struct MOTION { M4 local, world; char pad80[0x20]; MOTION *space; char padA4[0xC]; U velocity; char padC0[0x30]; U acceleration; };
struct LIMIT { char pad0[8]; float max; };
struct VTE { short delta, pad; void *fn; };
struct P {
    char pad0[0xC]; VTE *vt; char pad10[0x48 - 0x10]; MOTION *primary, *secondary;
    char pad50[0x1B0 - 0x50]; int state; char pad1B4[0x1DC - 0x1B4]; LIMIT *limit;
    char pad1E0[0x224 - 0x1E0]; float drive, turn; char pad22C[0x248 - 0x22C]; float height, lift;
};
struct CLOCK { float time, dt; };
extern CLOCK D_0036BB98;
extern const qword D_00317550;
extern char D_00325BA8[];
extern "C" {
void func_00243738(P *);
void func_00244890(P *, qword);
M3 *func_0011C8C0(M3 *, qword, float);
qword func_001205F0(qword, float);
qword func_0028E990(MOTION *, MOTION *, qword);
void func_00244828(P *, qword);
qword func_00120C80(qword, qword, void *, U *, float);
}
static inline VV ScalarBits(int b) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "rV"(b)); return r; }
static inline VV TimeStep(const CLOCK &c) { qword r; __asm__("qmtc2 %1,%0" : "=j"(r) : "rV"(*(const int *)&c.dt)); return r; }
static inline VV Subtract(VV a, VV b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline VV AddScaled(qword origin, qword axis, qword amount)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(origin), "j"(axis), "j"(amount));
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
static inline float Z(qword q) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(q)); return f; }
static inline M4 *PlacementOf(P *p)
{
    VTE *e = &p->vt[36];
    return ((M4 *(*)(void *))e->fn)((char *)p + e->delta);
}
static inline qword VelocityOf(P *p)
{
    VTE *e = &p->vt[38];
    return ((qword (*)(void *))e->fn)((char *)p + e->delta);
}
extern "C" void func_00214028(P *p)
{
    func_00243738(p);
    int state = p->state;
    if (state != 2) {
        if (state < 2) return;
        if (state >= 6) return;
        if (state < 4) return;
    }
    U localVelocity, torque, worldTorque;
    M3 basis;
    union PHASE { M3 rotation; struct { U scalar, velocity, desired, acceleration, world, limited; } impulse; } phase;
    U dtv, smoothed, offset, push, step;
    CLOCK *clock = &D_0036BB98;
    localVelocity.q = InverseRotate(p->secondary->local.basis, p->secondary->velocity.q);
    torque.f[0] = torque.f[1] = 0.0f;
    torque.f[2] = (p->turn - localVelocity.f[2]) / clock->dt;
    worldTorque.q = Rotate(p->secondary->world.basis, torque.q);
    func_00244890(p, worldTorque.q);
    float dt = clock->dt;
    float half = dt * 0.5f;
    func_0011C8C0(&phase.rotation, D_00317550, (localVelocity.f[2] + torque.f[2] * half) * dt);
    basis = phase.rotation;
    qword origin = p->primary->velocity.q;
    phase.impulse.velocity.q = ScalarBits(*(const int *)&clock->dt);
    phase.impulse.scalar.q = AddScaled(origin, p->primary->acceleration.q, phase.impulse.velocity.q);
    phase.impulse.velocity.q = func_0028E990(p->primary->space, p->secondary, phase.impulse.scalar.q);
    phase.impulse.desired.f[0] = p->drive;
    phase.impulse.desired.f[2] = phase.impulse.desired.f[1] = 0.0f;
    phase.impulse.desired.q = Rotate(basis, phase.impulse.desired.q);
    dtv.q = TimeStep(*clock);
    phase.impulse.acceleration.q = Divide(Subtract(phase.impulse.desired.q, phase.impulse.velocity.q), dtv.q);
    if (p->limit)
        phase.impulse.limited.q = func_001205F0(phase.impulse.acceleration.q, p->limit->max);
    else
        phase.impulse.limited.q = phase.impulse.acceleration.q;
    phase.impulse.world.q = func_0028E990(p->secondary, 0, phase.impulse.limited.q);
    phase.impulse.world.bits[2] = 0;
    func_00244828(p, phase.impulse.world.q);
    dtv.q = PlacementOf(p)->position.q;
    float height = p->height;
    dtv.f[2] = height;
    if ((unsigned)(p->state - 5) < 2)
        dtv.f[2] = height + p->lift;
    func_00120C80(PlacementOf(p)->position.q, dtv.q, D_00325BA8, &smoothed, D_0036BB98.dt);
    float vz = Z(VelocityOf(p));
    offset.bits[0] = 0;
    offset.f[2] = vz;
    offset.bits[1] = 0;
    step.q = TimeStep(D_0036BB98);
    push.q = Divide(Subtract(smoothed.q, offset.q), step.q);
    func_00244828(p, push.q);
}

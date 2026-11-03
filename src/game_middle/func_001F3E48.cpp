// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Damped spring step for a point: velocity += (offset * spring + velocity * damping) * dt, then the position advances
// with the average of the old and new velocity (dt is capped at 0.1).
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Sub(VU_VECTOR a, VU_VECTOR b)
{
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a.q), "j"(b.q));
    return d;
}
// f1 * v1 + f2 * v2
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
// a + b * s
static inline qword AddScaled(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q));
    return r;
}
// a + (b + c) * s; the repeated "j"(s.q) input is allocation-only (it raises the local-alloc priority of s)
static inline qword AddScaled2(VU_VECTOR a, VU_VECTOR b, VU_VECTOR c, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %4x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(c.q), "j"(s.q), "j"(s.q));
    return r;
}
extern "C" void func_001F3E48(qword target, qword *position, qword *velocity, float damping, float spring, float dt)
{
    dt = dt < 0.1f ? dt : 0.1f;
    qword accel = VecCombo(spring, Sub(target, *position), damping, *velocity);
    qword newVelocity = AddScaled(*velocity, accel, dt);
    *position = AddScaled2(*position, *velocity, newVelocity, dt * 0.5f);
    *velocity = newVelocity;
}

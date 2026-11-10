// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Steering toward a point for a target object: when the steer vector of the target is off-centre (|x| above a threshold)
// or below the target's minimum z, the heading error to `position` is limited by a dead zone, the target's matrix is
// turned by that error about the z axis, and the point is brought into that turned frame to give the turn rate (y).
typedef int qword __attribute__((mode(TI)));
union UQ { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct Method { short delta, pad; void *(*call)(void *); };
struct Target {
    char pad0[0xC];
    Method *vt;
    char pad10[0x118 - 0x10];
    float x118;
    char pad11C[0x134 - 0x11C];
    float x134;
    char pad138[0x13C - 0x138];
    float x13C;
    char pad140[0x144 - 0x140];
    float zMin;
};
struct Self {
    char pad0[0x3C];
    Target *target;
};
extern "C" {
extern float D_0034944C;
extern float D_00349450;
extern qword D_00317550;
qword func_001678C8(Target *target);
float func_001205C8(qword v);
float func_0011E3B8(float angle);
float func_0011E560(float g, float gMax);
M3 func_0011C8C0(float angle, qword axis);
M3 func_0011C6F8(M3 *pm);
}
static inline M4 *Matrix(Target *o)
{
    Method &m = o->vt[36];
    return (M4 *)m.call((char *)o + m.delta);
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Transform(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline M3 Mul(const M3 &a, const M4 &b) return r
{
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[0]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[1]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[2]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
}
extern "C" qword func_00222890(Self *self, qword position)
{
    UQ result;
    result.q = func_001678C8(self->target);
    if (__builtin_fabsf(result.f[0]) > D_0034944C || result.f[2] < self->target->zMin) {
        M3 mat;
        float angle = func_001205C8(Sub(position, Matrix(self->target)->r[3]));
        float heading = func_001205C8(Matrix(self->target)->r[0]);
        angle = func_0011E3B8(angle - heading);
        float width = (1.0f - D_0034944C) * self->target->x118 * self->target->x134;
        float turn;
        if (angle < 0.0f) {
            float t = angle + width;
            turn = t < 0.0f ? t : 0.0f;
        } else {
            float t = angle - width;
            turn = t > 0.0f ? t : 0.0f;
        }
        mat = Mul(func_0011C8C0(turn, D_00317550), *Matrix(self->target));
        UQ local;
        M3 inv = func_0011C6F8(&mat);
        local.q = Transform(inv, Sub(position, Matrix(self->target)->r[3]));
        float side = D_0034944C;
        if (0.0f < angle)
            side = -side;
        result.f[1] = local.f[2] / (local.f[0] * self->target->x13C);
        result.f[0] = side;
        result.f[2] = 0.0f;
    }
    result.f[1] = func_0011E560(result.f[1], D_00349450);
    return result.q;
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Updates the next steering time from the wait interval or a projected collision.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct M4 { qword r[4]; };
union Packed { qword q; float f[4]; };
struct Clock { float time, step; };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); }
};
struct GPR_FLOAT { qword qw; GPR_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(qw) : "f"(f)); } };
struct Hit { qword q[4]; float t0, t1; int count; void *o0, *o1; };
struct Actor {
    unsigned char prefix0[0xC];
    Method *methods;
    unsigned char gap10[0x250 - 0x10];
    float wait;
    float reach;
    float next;
};
extern Clock D_0036BB98;
extern qword D_00317560;
extern "C" {
void func_001D6C98(Actor *self);
Packed func_001D7250(Actor *self, float time);
qword func_001205F0(qword v, float limit);
int func_00164B08(qword a, qword b, qword c, int n, Hit *hit, float r);
}
static inline M4 *Matrix(Actor *self)
{
    Method *method = &self->methods[36];
    return ((M4 *(*)(void *))method->function)((char *)self + method->adjustment);
}
static inline qword Velocity(Actor *self)
{
    Method *method = &self->methods[38];
    return ((qword (*)(void *))method->function)((char *)self + method->adjustment);
}
static inline qword Mul(VU_FLOAT s, qword v) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.qw), "j"(v)); return r; }
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Sub(VU_VECTOR a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b)); return r; }
static inline qword AddScale(GPR_FLOAT s, qword b, qword a)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.qw), "jm"(s.qw)); /* The second scalar operand only affects allocation; it emits no instruction. */
    return r;
}
static inline float Max(float a, float b) { return (a < b) ? b : a; }
extern "C" void func_001D70E0(Actor *self)
{
    func_001D6C98(self);
    float wait = self->wait;
    float next;
    if (0.0f < wait) {
        next = D_0036BB98.time + wait;
    } else {
        Packed dir;
        dir = func_001D7250(self, 0.5f);
        Packed velocity;
        velocity.q = Mul(VU_FLOAT(-0.5f), Velocity(self));
        qword v = func_001205F0(velocity.q, self->reach * 0.75f);
        velocity.q = v;
        Packed target;
        target.q = AddScale(GPR_FLOAT(1.5f), Sub(dir.q, Matrix(self)->r[3]), v);
        Hit hit;
        func_00164B08(D_00317560, velocity.q, target.q, 1, &hit, self->reach);
        register float t1 __asm__("$f0") = hit.t1; /* match the saved hit-time register */
        __asm__("" : "+f"(t1)); /* Retain the original register through the clamp. */
        next = D_0036BB98.time + 1.0f / Max(0.25f, t1);
    }
    self->next = next;
}


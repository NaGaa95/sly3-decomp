// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Steers the actor toward its wanted position: when the wanted point equals the rest point (D_00317560), the end velocity is
// built from 1.5/rem * (dir - position) - 0.5 * velocity; a Hermite step (func_00118558) then gives the next position and the
// new velocity (next - velocity) / dt is applied with func_00244828.
// Allocation notes:
// - dir is a plain qword taken from the union returned through the hidden pointer (ret temp 0x0, dir spilled to 0x30).
// - VecCombo takes its scalars as GPR_FLOAT by value (the param copy is the dead sq at 0x10); the two trailing "jm" operands are
//   allocation-only: they make the scalars VU-class (spilled to 0x40/0x60) without adding reload needs.
// - VU_FLOAT reads the step word with "rV", so the load becomes a reload into the dying clock pointer register (lw s1,4(s1)).
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct M4 { qword r[4]; };
union Packed { qword q; float f[4]; };
struct Clock { float time, step; };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "rV"(*(const int *)&f)); }
};
struct Actor {
    unsigned char prefix0[0xC];
    Method *methods;
    unsigned char gap10[0x1CC - 0x10];
    int x1CC;
    unsigned char gap1D0[0x258 - 0x1D0];
    float until;
    unsigned char gap25C[4];
    qword wanted;
};
extern Clock D_0036BB98;
extern qword D_00317560;
extern "C" {
Packed func_001D7250(Actor *self, float time);
int func_0011E9F0(float a, float b, float eps);
void func_00118558(float tMax, float t, float s, qword a, qword va, qword b, qword vb, qword *ppos, qword *pv, int n);
void func_00244828(Actor *self, qword v);
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
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
struct GPR_FLOAT { qword qw; GPR_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(qw) : "f"(f)); } };
static inline qword VecCombo(GPR_FLOAT s1, qword a, GPR_FLOAT s2, qword b)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(s1.qw), "j"(a), "j"(s2.qw), "j"(b), "jm"(s1.qw), "jm"(s2.qw)); /* "jm" operands: allocation only */
    return r;
}
static inline qword Scale(qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(s.qw), "j"(v));
    return r;
}
static inline int Near(float a, float b) { return func_0011E9F0(a, b, 1.0e-4f); }
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float Max(float a, float b) { return a > b ? a : b; }
static inline float Min(float a, float b) { return a < b ? a : b; }
extern "C" void func_001D7320(Actor *self)
{
    if (self->x1CC)
        return;
    float rem = Max(self->until - D_0036BB98.time, 0.0f) + D_0036BB98.step;
    qword dir = func_001D7250(self, Min(rem, 0.5f)).q;
    qword wanted = self->wanted;
    qword rest = D_00317560;
    int same = 0;
    if (Near(GetX(rest), GetX(wanted)) && Near(GetY(rest), GetY(wanted)))
        same = Near(GetZ(rest), GetZ(wanted)) != 0;
    Packed out;
    if (same)
        out.q = VecCombo(GPR_FLOAT(1.5f / rem), Sub(dir, Matrix(self)->r[3]), GPR_FLOAT(-0.5f), Velocity(self));
    else
        out.q = self->wanted;
    Packed hermite;
    float dt = D_0036BB98.step;
    func_00118558(rem, dt, 1.0f, Matrix(self)->r[3], Velocity(self), dir, out.q, 0, &hermite.q, 0);
    qword h = hermite.q;
    func_00244828(self, Scale(Sub(h, Velocity(self)), VU_FLOAT(D_0036BB98.step)));
}

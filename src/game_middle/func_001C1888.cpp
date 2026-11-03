// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Steering update of the player: converts the stick input into a heading-relative acceleration, strips the
// sideways velocity component when the side flips, and blends the acceleration from the three axis rows.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); }
    // the raw-bits form is volatile: its qmtc2 stays ordered against the memory accesses around it
    VU_FLOAT(int bits) { __asm__ volatile("qmtc2.ni %1, %0" : "=j"(qw) : "r"(bits)); }
};
struct VT { short delta, pad; void *fn; };
struct Anim { char pad[0x40]; int rate; };
struct Target { char pad[0x4AC]; void *x4AC; };
struct M4 { qword r[4]; };
struct Axes { char pad[0x10]; qword r[11]; };
struct P {
    char pad0[0xC]; VT *vt;
    char pad10[0x1A0 - 0x10]; U acceleration;
    char pad1B0[0x1BC - 0x1B0]; float heading;
    char pad1C0[0x113C - 0x1C0]; Anim *anim; int pad1140; int side;
    char pad1148[0x11B4 - 0x1148]; Target *target; int pad11B8; int mode;
};
extern "C" {
int func_0013B500(void *o, int kind);
void func_0024E920(P *p, void *t);
float func_0011E3B8(float a);
qword func_0011FD70(float a, float b, float c);
}
static inline qword GetVel(P *p) { return ((qword (*)(void *))p->vt[38].fn)((char *)p + p->vt[38].delta); }
static inline M4 *GetFrame(P *p) { return ((M4 * (*)(void *))p->vt[36].fn)((char *)p + p->vt[36].delta); }
static inline void SetVel(P *p, qword v) { ((void (*)(void *, qword))p->vt[40].fn)((char *)p + p->vt[40].delta, v); }
static inline qword ToVu(qword bits) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(bits)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword ScaleX(qword v, qword k) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(k)); return r; }
static inline void MulXAssign(qword &d, qword n) { __asm__("vmulx.xyzw %0,%1,%0x" : "+j"(d) : "j"(n)); }
// the trailing "j"(v) is an allocation-only operand: it makes the velocity worth keeping in a VU register across the call
static inline void SubAssign(qword &v, qword d) { __asm__("vsub.xyzw %0,%0,%1" : "+j"(v) : "j"(d), "j"(v)); }
static inline qword Blend(qword a, VU_FLOAT ka, qword b, VU_FLOAT kb, qword c, VU_FLOAT kc)
{
    qword r;
    __asm__("vmulax.xyzw ACC,%1,%4x\n\tvmaddax.xyzw ACC,%2,%5x\n\tvmaddx.xyzw %0,%3,%6x" : "=j"(r) : "j"(a), "j"(b), "j"(c), "0"(ka.qw), "j"(kb.qw), "j"(kc.qw));
    return r;
}
static inline float Min(float a, float b) { return (b < a) ? b : a; }
static inline float Max(float a, float b) { return (b > a) ? b : a; }
// removes the component of the velocity along the side axis (frame row 1)
static inline void RemoveSideVelocity(P *p)
{
    qword old = ToVu(GetVel(p));
    M4 *basis = GetFrame(p);
    qword d = Dot(old, basis->r[1]);
    MulXAssign(d, basis->r[1]);
    SubAssign(old, d);
    U res;
    res.q = old;
    SetVel(p, res.q);
}
extern "C" void func_001C1888(P *p, Axes *axes, int active, float heading, float speed)
{
    U input;
    int side;
    float zero;
    if (!active)
        return;
    if (p->target)
        func_0024E920(p, (p->mode == 3 && func_0013B500(p->target, 0x3A)) ? p->target->x4AC : (void *)p->target);
    zero = 0.0f;
    input.q = func_0011FD70(func_0011E3B8(heading - p->heading), speed, zero);
    if (0.3f < input.f[1]) {
        if (p->side == 0) {
            input.f[1] = zero;
            RemoveSideVelocity(p);
        }
        side = 1;
    } else if (input.f[1] < -0.3f) {
        if (p->side == 1) {
            input.f[1] = zero;
            RemoveSideVelocity(p);
        }
        side = 0;
    } else {
        side = p->side;
        if (side == -1)
            side = 0;
    }
    if (side == 1) {
        float x = input.f[0];
        p->acceleration.q = Blend(axes->r[2], VU_FLOAT(input.f[1]), axes->r[6], VU_FLOAT(Max(0.0f, x)), axes->r[10], VU_FLOAT(-Min(0.0f, x)));
    } else {
        float x = input.f[0];
        p->acceleration.q = Blend(axes->r[0], VU_FLOAT(-input.f[1]), axes->r[4], VU_FLOAT(Max(0.0f, x)), axes->r[8], VU_FLOAT(-Min(0.0f, x)));
    }
    p->acceleration.f[2] = 0.0f;
    qword acc = p->acceleration.q;
    p->acceleration.q = ScaleX(acc, VU_FLOAT(p->anim->rate).qw);
    p->side = side;
}

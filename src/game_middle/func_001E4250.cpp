// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Late update of the actor's movement while it is in state 0x16 (callback of func_001DEF10). Mode 2 turns the current velocity
// into a damped push (planar and vertical response curves, clamped); mode 0 blends two sets of response curves by the blend
// factor, steers toward the heading, and unless the actor is held, pulls the velocity toward the target velocity (adding a
// downward correction while rising above the ground level).
// Allocation notes:
// - PlanarLength converts through a reload (ToFloat with a VU input), the form that schedules like the original.
// - AbsZ is its own helper (separate asm statement) so the second z extraction of Make's argument is not merged by cse.
// - MakeW keeps the built vector in a union local (dead stack store, shares the VU_FLOAT temp slot).
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Poly { float constant, linear, quadratic; };
struct Limits { float minimum, maximum; };
struct Matrix3 { qword row[3]; };
struct Input { unsigned char prefix[8]; float strength; };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); }
};
union Vector { qword q; float f[4]; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x134 - 0x10];
    struct Input *input;
    unsigned char gap138[0x1BC - 0x138];
    float heading;
    Matrix3 frame;
    unsigned char gap1F0[0x320 - 0x1F0];
    unsigned char context320[0x1AD4 - 0x320];
    int mode;
    unsigned char gap1AD8[0x1B00 - 0x1AD8];
    int held;
    unsigned char gap1B04[0x1B18 - 0x1B04];
    float blend;
};
extern "C" {
extern qword D_00317550;
extern qword D_00317490;
extern Poly D_00324AC0, D_00324AD0, D_00324AE0, D_00324AF0, D_00324B00, D_00324B10;
extern char D_00324AA8[];
extern Limits D_00341FF0;
extern float D_0047A470;
void func_0011CCF8(Matrix3 *m, Matrix3 *a, Matrix3 *b);
void func_0023EDE8(Actor *self, void *a, void *b);
qword func_0011FD70(float a, float b, float c);
void func_0023EFA0(Actor *self, void *table, int zero, qword v, float *out);
void func_001B8570(void *context, qword *v);
void func_00244828(Actor *self, qword v);
}
static inline Matrix3 *Frame(Actor *a)
{
    Method *m = &a->methods[36];
    return ((Matrix3 *(*)(void *))m->function)((char *)a + m->adjustment);
}
static inline qword Velocity(Actor *a)
{
    Method *m = &a->methods[38];
    return ((qword (*)(void *))m->function)((char *)a + m->adjustment);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulXq(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(s), "j"(a)); return r; }
static inline qword MulX(qword a, VU_FLOAT s) { return MulXq(a, s.qw); }
static inline qword MulAdd(qword a, VU_FLOAT s, qword b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.qw));
    return r;
}
static inline qword DotQ(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword PlanarLengthQ(qword v)
{
    qword d;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    return d;
}
static inline float ToFloat(qword q) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q)); return g; }
static inline float PlanarLength(qword v) { return ToFloat(PlanarLengthQ(v)); }
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float AbsZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return __builtin_fabsf(z); }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword MakeW(float x, float y, float z)
{
    Vector w;
    w.q = Make(x, y, z);
    return w.q;
}
static inline float Eval(const Poly *p, float t) { return p->constant + t * (p->linear + t * p->quadratic); }
static inline float Clamp(float value, const Limits *lim)
{
    float low = lim->minimum;
    float high = lim->maximum;
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
extern "C" void func_001E4250(Actor *self)
{
    switch (self->mode) {
    case 2: {
        Matrix3 m = *Frame(self);
        Matrix3 unused;
        func_0011CCF8(&m, 0, &unused);
        func_0023EDE8(self, &self->frame, D_00324AA8);
        qword v = Velocity(self);
        float lift = Clamp(Eval(&D_00324AC0, PlanarLength(v) * 0.0016666667f), &D_00341FF0);
        float drop = Clamp(Eval(&D_00324AD0, AbsZ(v) * 0.0016666667f), &D_00341FF0);
        func_00244828(self, MulX(MakeW(lift * GetX(v), lift * GetY(v), drop * GetZ(v)), VU_FLOAT(-10.0f)));
        break;
    }
    case 0: {
        float speed = (1.0f - self->blend) * 10.0f + self->blend * 14.0f;
        float s = (1.0f - self->blend) * self->input->strength + self->blend;
        qword dir = func_0011FD70(self->heading + 1.5707964f, speed * s, 0.0f);
        float out[4];
        out[0] = 0.0f;
        out[2] = 0.0f;
        out[1] = (1.0f - self->blend) * Eval(&D_00324AE0, s) + self->blend * Eval(&D_00324AF0, s);
        func_0023EFA0(self, &D_00317490, 0, dir, out);
        if (self->held)
            break;
        qword vel = Velocity(self);
        qword flat = Sub(vel, MulXq(D_00317550, DotQ(vel, D_00317550)));
        qword target = func_0011FD70(self->heading, s * 515.0f, 0.0f);
        float mix = (1.0f - self->blend) * Eval(&D_00324B00, s) + self->blend * Eval(&D_00324B10, s);
        Vector accel;
        accel.q = MulX(Sub(target, flat), VU_FLOAT(mix));
        int rising = 0;
        if (GetZ(((qword *)Frame(self))[3]) > D_0047A470 && GetZ(flat) >= 0.0f)
            rising = 1;
        if (rising)
            accel.q = MulAdd(accel.q, VU_FLOAT(GetZ(flat) * -4.5f), D_00317550);
        func_001B8570(self->context320, &accel.q);
        func_00244828(self, accel.q);
        break;
    }
    }
}

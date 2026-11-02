// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Contact response of an object with a water body: the penetration depth of the object's probe segment is found; the object
// is pushed back with a force scaled by both bodies' factors and the depth (capped at 1), turned towards the surface normal,
// slowed by a drag on its velocity and damped in its angular motion; the resulting impulse is applied to the water body.
// A shallow contact with an upward normal spawns the wake (func_00178278), anything else releases the object's wake handle.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct MATRIX4 { qword r[4]; };
#define VF1(n) virtual void V##n();
struct LO {
    int hdr[3];
    VF1(1) VF1(2) VF1(3) VF1(4) VF1(5) VF1(6) VF1(7) VF1(8) VF1(9) VF1(10) VF1(11) VF1(12) VF1(13) VF1(14) VF1(15) VF1(16)
    VF1(17) VF1(18) VF1(19) VF1(20) VF1(21) VF1(22) VF1(23) VF1(24) VF1(25) VF1(26) VF1(27) VF1(28) VF1(29) VF1(30) VF1(31)
    VF1(32) VF1(33) VF1(34) VF1(35)
    virtual MATRIX4 *PmatWorld();                                // 36
    VF1(37)
    virtual qword AngularVelocity();                             // 38
    virtual qword Velocity();                                    // 39
};
struct Vec3 { float x, y, z; };
struct BODY { char pad0[0x80]; qword velocity; char pad90[0xD4 - 0x90]; float factor; };
struct SO : LO {
    char pad10[0xD8 - 0x10]; BODY *body; float *box; char padE0[0x150 - 0xE0]; void *handle; char pad154[0x190 - 0x154];
    qword bias; Vec3 damp; char padAC[4]; float g1B0, g1B4, g1B8;   // angular bias, drag per axis, linear drag (base, speed), turn gain
};
struct CLOCK { float time, dt; };
extern CLOCK D_0036BB98;
extern qword D_00317530;        // default direction
extern qword D_00317550;
extern qword D_00317560;        // zero vector
// probe segment ends in the object frame
extern qword D_00325B40, D_00325B50;
extern "C" {
qword func_001C9428(SO *, SO *, qword);
qword func_001C94E8(SO *, SO *, qword);
float func_00280F70(SO *, qword, qword, qword *, qword *);
void func_00244828(SO *, qword);
void func_00244890(SO *, qword);
void func_00280598(SO *, qword, qword *, int);
int func_0011E9F0(float, float, float);
void func_00178278(SO *, SO *, qword, qword, float, float, float);
void func_00244CA8(void *, float);
void func_002BBCD8(void *, void *);
}
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
static inline qword Pack(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Scalar(float f) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline qword ScalarFromWord(const float &f) { qword r; int w = *(const int *)&f; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(w)); return r; }
static inline qword Scale(qword v, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Dot(qword a, qword b)
{
    qword r, one;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=&j"(one) : "j"(a), "j"(b));
    int n;
    __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(r));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(n));
    return f;
}
static inline qword Cross(qword a, qword b) { qword r; __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Length(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float GFromVfBits(qword v)
{
    int n;
    float g;
    __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(v));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(n));
    return g;
}
static inline qword Div(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
static inline qword Normalize(qword v)
{
    qword fallback = D_00317530;
    qword l = Length(v);
    if (GFromVfBits(l) < 0.0001f)
        l = fallback;
    else
        l = Div(v, l);
    return l;
}
static inline qword Drag(const Vec3 &k, qword w, qword bias)
{
    float x = GetX(w), y = GetY(w), z = GetZ(w);
    return Pack((k.x * __builtin_fabsf(x) + GetX(bias)) * -x, (k.y * __builtin_fabsf(y) + GetY(bias)) * -y,
                (k.z * __builtin_fabsf(z) + GetZ(bias)) * -z);
}
static inline float Min(float a, float b) { return b < a ? b : a; }
static inline int PositionNear(qword first, qword second)
{
    return func_0011E9F0(GetX(first), GetX(second), 0.0001f) && func_0011E9F0(GetY(first), GetY(second), 0.0001f) &&
           func_0011E9F0(GetZ(first), GetZ(second), 0.0001f);
}
extern "C" void func_0020EEF0(SO *self, SO *other)
{
    qword a = func_001C9428(self, 0, D_00325B40);
    qword b = func_001C9428(self, 0, D_00325B50);
    U hit0, hit1;
    float depth = func_00280F70(other, a, b, &hit0.q, &hit1.q);
    if (depth < 0.0001f)
        return;
    U k;
    U pk;
    k.q = Scalar(-(self->body->factor * other->body->factor) * Min(depth, 1.0f));
    func_00244828(self, Scale(self->body->velocity, k.q));
    qword n = func_001C94E8(self, 0, D_00317550);
    float d = Dot(n, hit1.q);
    qword axis = Cross(n, hit1.q);
    if (d < 0.0f)
        axis = Normalize(axis);
    k.q = ScalarFromWord(self->g1B8);
    func_00244890(self, Scale(axis, k.q));
    qword vel = self->Velocity();
    k.q = Scalar(-(GetX(Length(vel)) * self->g1B4 + self->g1B0));
    func_00244890(self, Scale(vel, k.q));
    func_00280598(other, self->PmatWorld()->r[3], &k.q, 0);
    qword w = Sub(self->AngularVelocity(), k.q);
    qword s = func_001C94E8(0, self, w);
    qword *pDir = !PositionNear(D_00317560, k.q) ? &D_00317560 : &self->bias;
    pk.q = Drag(self->damp, s, *pDir);
    func_00244828(self, func_001C94E8(self, 0, pk.q));
    if (0.0f < depth && depth < 1.0f && hit1.f[2] > 0.9f) {
        float *box = self->box;
        func_00178278(self, other, k.q, hit0.q, D_0036BB98.dt, 0.1f, (box[4] - box[0] + (box[5] - box[1])) * 0.25f);
    } else {
        void **pp = &self->handle;
        if (pp && self->handle) {
            func_00244CA8(self->handle, 0.0f);
            func_002BBCD8(pp, 0);
        }
    }
}

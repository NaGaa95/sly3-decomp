// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Missile speed chase (same routine as Sly 2 ACCMISS::VUnk69, func_001B20B8): while the target flag is clear, ease the
// speed of the missile's velocity toward svTarget and hand the resulting acceleration to the physics constraint.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword qw; };
struct SMP { float svFast, svSlow, dtFast; };
struct CLOCK { float t, dt; };
struct Method { short delta, pad; qword (*function)(void *); };
struct Table { unsigned char prefix[0x130]; Method velocity; };
struct Physics { unsigned char prefix[0xB0]; };
struct Missile {
    unsigned char prefix0[0xC];
    Table *table;
    unsigned char gap10[0x48 - 0x10];
    void *frame;
    unsigned char gap4C[0xD8 - 0x4C];
    Physics *physics;
    unsigned char gapDC[0x1CC - 0xDC];
    int armed;
    unsigned char gap1D0[0x250 - 0x1D0];
    float svTarget;
    float svFast;
};
extern CLOCK D_0036BB98;
extern "C" {
float func_0011E598(float sv, float svTarget, SMP smp, float *next, float dt);
qword func_00244418(void *constraint, void *frame, qword value);
void func_00244828(void *self, qword velocity);
}
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline qword QwSub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float GFromVf(qword q)
{
    float g;
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(q));
    return g;
}
static inline qword QwLength(qword v)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "0"(r));
    return r;
}
static inline float GLength(qword v) { return GFromVf(QwLength(v)); }
static inline qword QwDivFloat(qword q, float g)
{
    VU_FLOAT d;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(d.qw) : "r"(g));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(d.qw), "j"(q));
    return r;
}
static inline qword QwDivBits(qword q, int bits)
{
    VU_FLOAT d;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(d.qw) : "rV"(bits));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(d.qw), "j"(q));
    return r;
}
static inline qword QwMulX(qword row, VU_FLOAT s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(row), "j"(s.qw));
    return r;
}
extern "C" void func_001D6F70(Missile *self)
{
    if (self->armed == 0) {
        qword qwVel = self->table->velocity.function((char *)self + self->table->velocity.delta);
        float sv = GLength(qwVel);
        qword qwDir = QwDivFloat(qwVel, sv);
        SMP smp = { self->svFast, 0.0f, 1.0f };
        float svNew = func_0011E598(sv, self->svTarget, smp, 0, D_0036BB98.dt);
        qword qwDv = QwDivBits(QwSub(QwMulX(qwDir, VuFloat(svNew)), qwVel), *(int *)&D_0036BB98.dt);
        func_00244828(self, func_00244418((char *)self->physics + 0xB0, self->frame, qwDv));
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef unsigned long long qword __attribute__((mode(TI)));
union QV { qword q; float f[4]; };
struct SMP { float gA, gB, gC; };
struct Params { unsigned char pad0[8]; float reach; };
struct Actor {
    unsigned char pad0[0x134]; Params *params;
    unsigned char pad138[0x260 - 0x138]; qword origin;
    unsigned char pad270[0x110C - 0x270]; float turnRate;
};
struct Self { Actor *actor; unsigned char pad4[0x260 - 4]; float x260; unsigned char pad264[0x2A0 - 0x264]; float x2A0; };
struct ClockStep { float now, step; };
extern "C" {
extern ClockStep D_0036BB98;
extern qword D_00317550;
extern qword D_00317560;
void func_0022E148(void *path, float t, qword *position, qword *direction);
qword func_0011FD70(float a, float b, float c);
float func_0022DD48(void *path, float t);
float func_0022DFD8(void *path);
float func_0011E598(float g, float gTarget, float dt, SMP *psmp, float *pdg);
}
static inline qword VuFloat(float g) { qword v; __asm__("qmtc2.ni %1,%0" : "=j"(v) : "r"(g)); return v; }
static inline qword QwSub(qword a, qword b) { __asm__("vsub.xyzw %0,%0,%1" : "+j"(a) : "j"(b)); return a; }
static inline float GFromVf(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline qword QwDot(qword a, qword b)
{
    qword one, d;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword QwLengthDot(qword v)
{
    qword d = QwDot(v, v);
    qword l;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword QwScaleRecip(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword QwMulX(qword v, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(s), "j"(v));
    return r;
}
static inline qword Normalized(qword diff, qword fallback)
{
    qword length = QwLengthDot(diff);
    if (GFromVf(length) < 0.0001f)
        return fallback;
    return QwScaleRecip(diff, length);
}
static inline float GLimit(float g, float gMin, float gMax)
{
    float r;
    if (g < gMin)
        r = gMin;
    else if (gMax < g)
        r = gMax;
    else
        r = g;
    return r;
}
extern "C" void func_001B5370(Self *self, void *path, qword *outOffset, qword *outVelocity, float t)
{
    QV position;
    QV direction;
    QV turn;
    SMP smp;
    QV scale;
    float low, high;
    Params *params = self->actor->params;
    float along, g;
    func_0022E148(path, t, &position.q, &direction.q);
    {
        qword up = D_00317550;
        qword fallback = D_00317560;
        qword d = QwDot(direction.q, up);
        direction.q = Normalized(QwSub(direction.q, QwMulX(up, d)), fallback);
    }
    turn.q = func_0011FD70(self->actor->turnRate, self->x2A0 * params->reach, 0.0f);
    along = GFromVf(QwDot(turn.q, direction.q));
    g = func_0022DD48(path, t);
    smp.gB = self->x260;
    smp.gA = self->x2A0;
    smp.gC = 0.2f;
    func_0011E598(g, 50.0f, D_0036BB98.step, &smp, &low);
    func_0011E598(g, func_0022DFD8(path) - 50.0f, D_0036BB98.step, &smp, &high);
    *outOffset = QwSub(position.q, self->actor->origin);
    scale.q = VuFloat(GLimit(along, low, high));
    *outVelocity = QwMulX(direction.q, scale.q);
}

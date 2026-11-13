// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of the path-riding object whose state setter is func_001BFAD0: picks the stick object (global pad from
// func_00156998 or the actor's own), drops off when the path is no longer flagged (bit 56) or on button 0x40, handles the
// 0x400 action button, loops the state machine (states 0/4 advance to 1 when the animation ends), samples the path 50 units
// ahead and behind and turns around (state 4) on a steep slope or a drift against the riding direction, then projects the
// stick onto the path direction (func_001681B0) to update the stick side (-1 idle, 0 forward, 1 back), the speed between
// speed0 and speed1, the smoothed drift, the limits from func_001BF128 (non-cyclic paths) and the blend weights.
// Source-shape notes: the normalized path direction is converted to a GPR qword once after the fallback join (QwNormalizeG),
// which keeps the two later Z() extractions separate from the first; one float local carries the dot product, the blend
// and the final weight (one register in the original); the pad vector is a union local that the SMP slot later reuses.
typedef unsigned long long qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct VE { short delta, pad; void *fn; };
union VU { qword q; float f[4]; };
struct LM { float gMin, gMax; };
struct SMP { float svFast, svSlow, dtFast; };
struct PAD { float x, y, amount; char pad0C[0x2C - 0xC]; VE *vt; };
struct ACTOR
{
    char pad0[0xC]; VE *vt;
    char pad10[0x134 - 0x10]; PAD *pad;
    char pad138[0x320 - 0x138]; char controller[0xF60 - 0x320]; char action[0x113C - 0xF60]; void *aseg;
};
struct PATH
{
    char pad0[0x28]; ulong flags;
    char pad30[0xD4 - 0x30]; int cyclic;
    char padD8[0x1E8 - 0xD8]; float gain;
};
struct ANIM;
struct S
{
    ACTOR *actor; int state; float tState; PATH *path; float u; float speed; int descending; float drift; int side;
    char pad24[0x50 - 0x24]; float weight0; char pad54[0x5C - 0x54]; float speed0; float weight1; char pad64[0x6C - 0x64]; float speed1;
    ANIM *anim;
};
struct CLOCK { float t; float dt; };
extern CLOCK g_clock;
extern qword D_00317550;
extern PAD D_0036E6D0;
extern "C" {
int func_00156998(ACTOR *);
void func_001B7268(void *, int, int, int, float);
int func_001A7A80(PAD *, int, float);
void func_001BDA88(void *, int, int);
int func_00138AC8(void *);
void func_001BFAD0(S *, int);
float func_0022E0B8(PATH *, float);
void func_0022E330(PATH *, float, qword *, qword *);
void *func_001F4A80(ACTOR *);
qword func_001681B0(void *, qword);
void func_001BF128(S *, LM *);
float func_0011E598(float, float, float, SMP *, float *);
void func_0023DD40(ACTOR *);
float func_0022DFD8(PATH *);
float func_0011EDB8(float, float);
void func_00148938(ANIM *);
float fabsf(float);
}
static inline int Pressed(PAD *a, int mask, float g) { VE *v = &a->vt[1]; return ((int (*)(void *, int, float))v->fn)((char *)a + v->delta, mask, g); }
static inline void Clear(PAD *a, int mask) { VE *v = &a->vt[2]; ((void (*)(void *, int))v->fn)((char *)a + v->delta, mask); }
static inline int Can(ACTOR *a, int n) { VE *v = &a->vt[113]; return ((int (*)(void *, int))v->fn)((char *)a + v->delta, n); }
static inline qword QwSub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword QwDot(qword a, qword b)
{
    qword qw, vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwLength(qword v)
{
    qword qw, qw2, vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw2) : "j"(qw));
    return qw2;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword Gpr(qword q) { qword r; __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(q)); return r; }
static inline float FX(qword q) { return F(Gpr(q)); }
static inline qword DivQ(qword qw, qword v)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(qw), "j"(v));
    return r;
}
static inline qword QwNormalize(qword v)
{
    qword qw = QwLength(v);
    qword fb = D_00317550;
    if (F(qw) < 1.0e-4f)
        return fb;
    return DivQ(qw, v);
}
static inline qword QwNormalizeG(qword v) { return Gpr(QwNormalize(v)); }
static inline float Z(qword q) { float w; __asm__("pextuw %0, $zero, %1" : "=r"(w) : "r"(q)); return w; }
static inline qword QwFromXYZ(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}

extern "C" void func_001BF1F8(S *p)
{
    PAD *pad = func_00156998(p->actor) ? &D_0036E6D0 : p->actor->pad;
    if (((int)(p->path->flags >> 56) & 1) == 0)
    {
        func_001B7268(p->actor->controller, 0, 0, 0, 1.0f);
        return;
    }
    if (p->state && func_001A7A80(pad, 0x40, 0.25f))
    {
        func_001B7268(p->actor->controller, 2, 0, 0, p->path->gain);
        return;
    }
    if (Pressed(pad, 0x400, 0.15f) && Can(p->actor, 3))
    {
        Clear(pad, 0x400);
        func_001BDA88(p->actor->action, 0, 0);
    }
    int old;
    do
    {
        old = p->state;
        if ((old == 0 || old == 4) && func_00138AC8(p->actor->aseg))
            func_001BFAD0(p, 1);
    } while (p->state != old);
    if (p->state == 0 || p->state == 4)
        return;
    VU ahead, behind;
    func_0022E330(p->path, func_0022E0B8(p->path, p->u + 50.0f), &ahead.q, 0);
    func_0022E330(p->path, func_0022E0B8(p->path, p->u - 50.0f), &behind.q, 0);
    qword n = QwNormalizeG(QwSub(ahead.q, behind.q));
    float z = Z(n);
    if (fabsf(z) > 0.5f)
    {
        if (z > 0.0f)
        {
            if (!p->descending)
                goto check;
            goto turn;
        }
        if (!p->descending)
            goto turn;
    }
check:
    if (p->drift > 0.4f && p->descending && Z(n) > -0.3f)
        goto turn;
    if (p->drift < -0.4f && !p->descending && Z(n) < 0.3f)
    {
turn:
        func_001BFAD0(p, 4);
        return;
    }
    {
        qword dir = func_001681B0(func_001F4A80(p->actor), QwSub(ahead.q, behind.q));
        float zero = 0.0f;
        float x = pad->x, y = pad->y;
        float amount = pad->amount;
        float g;
        {
            VU stick;
            stick.q = QwFromXYZ(x, y, zero);
            g = FX(QwDot(dir, stick.q));
        }
        switch (p->side)
        {
        case 0:
            if (amount < 0.25f)
                p->side = -1;
            else if (g < -0.7f)
                p->side = 1;
            break;
        case 1:
            if (amount < 0.25f)
                p->side = -1;
            else if (g > 0.7f)
                p->side = 0;
            break;
        case -1:
            if (amount > 0.35f)
            {
                if (zero <= g)
                    p->side = 0;
                else
                    p->side = 1;
            }
            break;
        }
        int mode = -1;
        switch (p->side)
        {
        case 0:
            mode = p->descending ? 3 : 2;
            g = amount;
            break;
        case 1:
            mode = p->descending ? 2 : 3;
            g = amount;
            break;
        case -1:
            mode = 1;
            g = 0.0f;
            break;
        }
        float speed;
        if (g > 0.01f)
        {
            speed = (1.0f - g) * p->speed0 + g * p->speed1;
            if (mode == 3)
                speed = -speed;
        }
        else
        {
            speed = 0.0f;
            mode = 1;
        }
        if (p->descending)
            speed = -speed;
        SMP smp;
        smp.svFast = fabsf(p->speed1);
        smp.dtFast = 0.2f;
        smp.svSlow = 0.0f;
        p->drift = (-g_clock.dt * speed) / smp.svFast + (1.0f - g_clock.dt) * p->drift;
        if (!p->path->cyclic)
        {
            LM lm;
            float dgMin, dgMax;
            func_001BF128(p, &lm);
            func_0011E598(p->u, lm.gMin, g_clock.dt, &smp, &dgMin);
            func_0011E598(p->u, lm.gMax, g_clock.dt, &smp, &dgMax);
            float lo = -dgMax, hi = -dgMin;
            if (speed < lo)
                speed = lo;
            else if (hi < speed)
                speed = hi;
        }
        float stopped = 0.0f;
        p->speed = -speed;
        if (speed != stopped)
        {
            p->u += p->speed * g_clock.dt;
            func_0023DD40(p->actor);
        }
        if (p->path->cyclic)
            p->u = func_0011EDB8(p->u, func_0022DFD8(p->path));
        float a = fabsf(speed);
        if (a < 0.01f)
            mode = 1;
        else
        {
            float s0 = fabsf(p->speed0);
            g = (a - s0) / (fabsf(p->speed1) - s0);
            float one = 1.0f;
            if (g < stopped)
                g = stopped;
            else if (one < g)
                g = one;
            p->weight1 = g;
            p->weight0 = 1.0f - g;
            func_00148938(p->anim);
        }
        func_001BFAD0(p, mode);
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001B30E8: per-frame update of a hero's movement/action context (Sly 2 func_00191A10 relative).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;

union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; };
struct M4 { U r[4]; };
struct VTE { short delta, pad; void *fn; };
struct VU_FLOAT { qword q; };

static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.q) : "r"(g)); return v; }
static inline qword QwZero() { qword r; __asm__("vsub.xyzw %0,$vf0,$vf0" : "=j"(r)); return r; }
static inline qword QwAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwScale(qword a, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(g.q)); return r; }
static inline qword QwScaleX(qword a, qword g) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(g), "j"(a)); return r; }
static inline float GFromVf(qword v) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(v)); return g; }
static inline qword QwDot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword QwSqrt(qword d) { qword r; __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(d)); return r; }
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline float GLength(VU_VECTOR v) { return GFromVf(QwSqrt(QwDot(v.q, v.q))); }
static inline float GLengthXY(qword v)
{
    qword l;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(l) : "j"(v));
    return GFromVf(QwSqrt(l));
}
static inline qword QwDiv(qword v, qword l)
{
    qword r;
    __asm__ __volatile__("vdiv $Q,$vf0w,%0x\n\tvwaitq" : : "j"(l));
    __asm__("vmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v));
    return r;
}
static inline qword QwNormalize(qword v, qword fallback)
{
    qword l = QwSqrt(QwDot(v, v));
    if (GFromVf(l) < 0.0001f)
        return fallback;
    return QwDiv(v, l);
}
// M * v (rows of M dotted with v); w comes from row 0
static inline qword QwMulM3(M3 *pm, qword v)
{
    qword r = pm->r[0].q;
    qword t0, t1, t2, one;
    __asm__("vmul.xyzw %2,%0,%5\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%5\n\tvmul.xyzw %4,%7,%5\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "+j"(r), "=&j"(one), "=&j"(t0), "=&j"(t1), "=&j"(t2) : "j"(v), "j"(pm->r[1].q), "j"(pm->r[2].q));
    return r;
}
static inline void SetXYZ(U *p, float x, float y, float z) { p->f[0] = x; p->f[1] = y; p->f[2] = z; }
static inline float SqrtF(float x) { float r; __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(x)); return r; }
static inline float GClamp(float g, float lo, float hi) { if (g < lo) return lo; else if (hi < g) return hi; else return g; }
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GMax(float a, float b) { return a < b ? b : a; }


struct JOY { float x, y, amount; };
struct ANIM { char pad0[0x14]; void *table; char pad18[4]; float phase; char pad20[0x20]; float rate; };
struct COMPONENT { VTE *vt; };
struct BINDING { int key; COMPONENT *component; };
struct SMP { float svFast, svSlow, dtFast; };
struct ENTRY { float weight; int active; char pad8[8]; U direction; };
struct PROGRAM { void *owner; void *clip; char pad8[0x18]; float x20; char pad24[0x3C]; float x60; char pad64[0x40]; };
struct FOCUS { char padD4[0xD4]; int cyclic; char padD8[0x188 - 0xD8]; int enabled; char pad18C[0x1CC - 0x18C]; uint flags; char pad1D0[8]; FOCUS *other; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x134 - 0x10]; JOY *pjoy; char pad138[0x148 - 0x138]; void *x148;
    char pad14C[0x1A0 - 0x14C]; U velocity; char pad1B0[0x1BC - 0x1B0]; float heading; M3 local;
    char pad1F0[0x110C - 0x1F0]; float stick; char pad1110[0x113C - 0x1110]; ANIM *anim; char pad1140[0x114C - 0x1140]; int role;
    char pad1150[0x1650 - 0x1150]; char x1650[0x100]; char pad1750[0x1AD8 - 0x1750];
};
struct CONTEXT {
    ACTOR *actor; float stamp; int action; int step; float tHold; FOCUS *focus; void *setting; float parameter;
    float value; int reversed; int index; float speed; int x30; char pad34[0x50 - 0x34]; float maximum; char pad54[0x68 - 0x54];
    void *x68; char pad6C[4]; ENTRY axes[8]; void *request; char pad174[0x180 - 0x174]; PROGRAM program180;
    char pad224[0x240 - 0x224]; PROGRAM program240; char pad2E4[0x330 - 0x2E4]; ENTRY axes2[8]; void *request2;
    char pad434[0x440 - 0x434]; char sub[0x10];
};
struct CLOCK { float t, dt; };

extern "C" {
extern CLOCK g_clock;
extern ACTOR *D_00370AC0;
extern char D_0036E6D0[];
extern qword D_00317530;                    // (1, 0, 0, 0)
extern SMP D_00322C18;
extern char D_00322C30[];
void func_001A0798(void *, ACTOR *, float *, U *, float *);
qword func_00120C80(qword, qword, float, SMP *, U *);
int func_0013B500(void *, int);
qword func_0011FD70(float, float, float);
float func_0022DFB0(FOCUS *);
float func_0022DFD8(FOCUS *);
float func_0022DFA0(FOCUS *);
float func_0022DFC0(FOCUS *);
float func_0011E598(float, float, float, SMP *, float *);
void func_001B5830(CONTEXT *, int);
void func_0024E878(ACTOR *, float);
float func_002A3EE8(float, float);
float func_0011E3B8(float);
void func_001B4430(CONTEXT *, int);
void func_00258CF0(PROGRAM *, float);
void func_00258DA0(PROGRAM *);
void func_0022E148(FOCUS *, float, U *, U *);
void func_001B7268(void *, int, int, int, float);
float func_001205C8(qword);
qword func_00250600(ACTOR *);
void func_0022EA88(FOCUS *, qword, void *, void *, U *, void *, void *);
float func_0022E058(FOCUS *, float);
float func_0022DE50(FOCUS *, float);
void func_0023DD40(ACTOR *);
void func_00208378(void *);
void func_001C1550(ACTOR *, ENTRY *, void *);
void func_0024FCA0(ACTOR *, void *);
BINDING *func_00136EE0(void *, ACTOR *, int, int);
void func_0024E920(ACTOR *, FOCUS *);
void func_0024F0B0(ACTOR *);
void func_001AB308(ACTOR *, void *, void *, void *, float, void *);
void func_001B55A0(ACTOR *, void *, void *);
int func_00156998(void *);
}

static inline M4 *MatrixOf(ACTOR *p) { VTE &v = p->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.delta); }
static inline qword GetVelocity(ACTOR *p) { VTE &v = p->vt[38]; return ((qword (*)(void *))v.fn)((char *)p + v.delta); }
static inline void ReadBinding(BINDING *b, ANIM *a, U *out)
{
    COMPONENT *c = b->component;
    VTE &v = c->vt[3];
    ((void (*)(void *, int, U *, float, float))v.fn)((char *)c + v.delta, 0, out, a->phase, a->rate);
}

extern "C" void func_001B30E8(CONTEXT *ctx)
{
    U pos;
    U velOld;
    pos.q = MatrixOf(ctx->actor)->r[3].q;
    velOld.q = GetVelocity(ctx->actor);
    JOY *pjoy = func_00156998(ctx->actor) ? (JOY *)D_0036E6D0 : ctx->actor->pjoy;
    float stick = ctx->actor->stick;

    switch (ctx->action) {
    case 0:
    case 13: {
        U goal;
        float heading;
        func_001A0798(ctx->setting, ctx->actor, &ctx->value, &goal, &heading);
        float speedMax;
        if (ctx->actor->role == 1)
            speedMax = GLength(ctx->axes[2].direction.q) * ctx->actor->anim->rate;
        else
            speedMax = GLength(ctx->axes[4].direction.q) * ctx->actor->anim->rate;
        goal.f[2] = pos.f[2];
        SMP smp;
        smp.svFast = speedMax;
        smp.svSlow = 0.0f;
        smp.dtFast = 0.3f;
        U vel;
        func_00120C80(pos.q, goal.q, g_clock.dt, &smp, &vel);
        float lateral;
        qword offset;
        if (func_0013B500(ctx->focus, 36)) {
            offset = QwZero();
            lateral = 0.0f;
        } else {
            U side;
            float angle;
            if (ctx->actor->role == 1)
                angle = heading - 1.5707964f;
            else
                angle = heading + 1.5707964f;
            side.q = func_0011FD70(angle, 1.0f, 0.0f);
            U input;
            input.q = func_0011FD70(stick, 1.0f, 0.0f);
            float g = GClamp(1.5f * GFromVf(QwDot(side.q, input.q)), -1.0f, 1.0f);
            g *= pjoy->amount;
            if (__builtin_fabsf(g) < 0.2f)
                g = 0.0f;
            lateral = g * speedMax;
            lateral = GMin(SqrtF(speedMax * speedMax - GFromVf(QwDot(vel.q, vel.q))), lateral);
            float s;
            FOCUS *focus;
            if (func_0013B500(ctx->focus, 11) && !(focus = ctx->focus)->cyclic) {
                float lo, hi;
                func_0011E598(ctx->value, func_0022DFB0(focus) + 30.0f, g_clock.dt, &smp, &lo);
                func_0011E598(ctx->value, func_0022DFD8(focus) - 30.0f, g_clock.dt, &smp, &hi);
                s = GClamp(lateral, lo, hi);
            } else {
                s = lateral;
            }
            offset = QwScale(side.q, VuFloat(s));
        }
        ACTOR *actor = ctx->actor;
        actor->velocity.q = QwScale(QwMulM3(&actor->local, QwAdd(vel.q, offset)), VuFloat(-1.0f));
        int step;
        if (25.0f < GLength(ctx->actor->velocity.q)) {
            step = 1;
            if (ctx->action == 0) {
                if (45.0f < GLength(vel.q)) {
                    func_001B5830(ctx, 0);
                } else if (20.0f < ctx->actor->velocity.f[1]) {
                    if (ctx->actor->role == 1)
                        func_001B5830(ctx, 1);
                    else
                        func_001B5830(ctx, 2);
                } else if (ctx->actor->velocity.f[1] < -20.0f) {
                    if (ctx->actor->role == 1)
                        func_001B5830(ctx, 2);
                    else
                        func_001B5830(ctx, 1);
                }
            }
        } else {
            step = 0;
            if (func_0013B500(ctx->focus, 11)) {
                FOCUS *focus = ctx->focus;
                if (lateral < -25.0f && (focus->flags & 1)) {
                    step = ctx->action == 0 && ctx->actor->role == 0 ? 3 : 2;
                } else if (25.0f < lateral && (focus->flags & 2)) {
                    step = ctx->action == 0 && ctx->actor->role == 0 ? 2 : 3;
                }
            }
            if (ctx->action == 0)
                func_001B5830(ctx, 3);
        }
        func_0024E878(ctx->actor, heading);
        if (ctx->step == 5) {
            M4 *m = MatrixOf(ctx->actor);
            if (0.25f < __builtin_fabsf(func_0011E3B8(func_002A3EE8(m->r[0].f[1], m->r[0].f[0]) - heading)))
                step = 5;
        }
        func_001B4430(ctx, step);
        break;
    }
    case 1:
        if (ctx->focus->enabled && 0.0f < pjoy->amount && ctx->program180.clip) {
            func_001B4430(ctx, 4);
            func_00258CF0(&ctx->program180, pjoy->amount);
            func_0024E878(ctx->actor, stick);
            func_00258DA0(&ctx->program180);
        } else {
            func_001B4430(ctx, 0);
        }
        break;
    case 2:
        if (ctx->step == 0 ? 0.1f < pjoy->amount : 0.0f < pjoy->amount) {
            func_001B4430(ctx, 4);
            func_00258CF0((PROGRAM *)((char *)ctx->actor + 0x1C90), pjoy->amount * 0.75f);
        } else {
            func_001B4430(ctx, 0);
            break;
        }
        // fall through: face the stick
    case 4:
        func_0024E878(ctx->actor, stick);
        break;
    case 3: {
        FOCUS *focus = ctx->focus;
        U point, tangent;
        func_0022E148(focus, ctx->parameter, &point, &tangent);
        if (focus->flags && !focus->cyclic &&
            (ctx->parameter < func_0022DFA0(focus) + 0.01f || func_0022DFC0(focus) - 0.01f < ctx->parameter)) {
            func_001B7268((char *)ctx->actor + 0x320, 0, 0, 0, 1.0f);
            break;
        }
        tangent.f[2] = 0.0f;
        tangent.q = QwNormalize(tangent.q, D_00317530);
        float heading = func_001205C8(tangent.q);
        U dir;
        U input;
        input.q = func_0011FD70(stick, 1.0f, 0.0f);
        if (!focus->other)
            dir = tangent;
        else
            func_0022EA88(focus->other, func_00250600(ctx->actor), 0, 0, &dir, 0, 0);
        dir.f[2] = 0.0f;
        dir.q = QwNormalize(dir.q, D_00317530);
        float g = GFromVf(QwDot(input.q, dir.q));
        switch (ctx->index) {
        case 0:
            if (pjoy->amount < 0.25f)
                ctx->index = -1;
            else if (g < -0.7f)
                ctx->index = 1;
            break;
        case 1:
            if (pjoy->amount < 0.25f)
                ctx->index = -1;
            else if (0.7f < g)
                ctx->index = 0;
            break;
        case -1:
            if (0.35f < pjoy->amount) {
                if (0.0f <= g)
                    ctx->index = 0;
                else
                    ctx->index = 1;
            }
            break;
        }
        switch (ctx->index) {
        case 0:
            ctx->reversed = 0;
            break;
        case 1:
            ctx->reversed = 1;
            break;
        }
        if (focus->flags) {
            g = 0.0f;
        } else {
            SMP smp;
            float limit;
            smp.svSlow = ctx->program240.x20;
            smp.svFast = ctx->program240.x60;
            smp.dtFast = 0.2f;
            if (focus->cyclic) {
                limit = smp.svFast;
            } else if (ctx->reversed) {
                func_0011E598(ctx->value, 50.0f, g_clock.dt, &smp, &limit);
                limit = -limit;
            } else {
                func_0011E598(ctx->value, func_0022DFD8(focus) - 50.0f, g_clock.dt, &smp, &limit);
            }
            float ratio = (limit - smp.svSlow) / (smp.svFast - smp.svSlow);
            float amount = pjoy->amount;
            if (amount < 0.0f)
                g = 0.0f;
            else if (ratio < amount)
                g = ratio;
            else
                g = amount;
        }
        if (ctx->reversed)
            heading = func_0011E3B8(heading + 3.1415927f);
        float speed;
        if (0.01f < g) {
            func_001B4430(ctx, 4);
            func_00258CF0(&ctx->program240, g);
            func_0024E878(ctx->actor, heading);
            func_00258DA0(&ctx->program240);
            speed = GLength(ctx->actor->velocity.q);
            if (ctx->reversed)
                speed = -speed;
        } else {
            func_001B4430(ctx, 0);
            func_0024E878(ctx->actor, heading);
            speed = 0.0f;
        }
        ctx->speed = func_0011E598(ctx->speed, speed, g_clock.dt, &D_00322C18, 0);
        float v = ctx->value + ctx->speed * g_clock.dt;
        if (focus->cyclic)
            v = func_0022E058(focus, v);
        else
            v = GClamp(v, 50.0f, func_0022DFD8(focus) - 50.0f);
        ctx->value = v;
        ctx->parameter = func_0022DE50(focus, v);
        func_0023DD40(ctx->actor);
        break;
    }
    case 5:
    case 9:
        func_00208378(ctx->sub);
        break;
    case 8:
        switch (ctx->step) {
        case 7:
        case 8:
            break;
        default:
            if (0.0f < pjoy->amount) {
                func_001B4430(ctx, 10);
                ENTRY *e = &ctx->axes2[3];
                if (!e->active)
                    e = &ctx->axes2[2];
                SetXYZ(&ctx->actor->velocity, -pjoy->y * GLengthXY(e->direction.q), pjoy->x * GLengthXY(ctx->axes2[1].direction.q), 0.0f);
                func_001C1550(ctx->actor, ctx->axes2, ctx->request2);
                ACTOR *actor = ctx->actor;
                float turn = -actor->velocity.f[1] / 55.0f;
                actor->velocity.q = QwScaleX(D_00317530, QwDot(actor->velocity.q, D_00317530));
                func_0024E878(ctx->actor, ctx->actor->heading + turn * g_clock.dt);
            } else {
                func_001B4430(ctx, 9);
            }
            if (ctx->actor == D_00370AC0)
                func_0024FCA0(ctx->actor, D_00322C30);
            break;
        }
        break;
    case 10: {
        U v;
        v.f[2] = 0.0f;
        v.f[1] = 0.0f;
        v.f[0] = 0.0f;
        ACTOR *actor = ctx->actor;
        ANIM *anim = actor->anim;
        if (anim) {
            BINDING *b = func_00136EE0(anim->table, actor, 1, 1);
            if (b) {
                ReadBinding(b, anim, &v);
                v.q = QwScale(v.q, VuFloat(-1.0f));
            }
        }
        ctx->actor->velocity = v;
        break;
    }
    case 11:
        if (ctx->focus) {
            func_0024E920(ctx->actor, ctx->focus);
            func_0024F0B0(ctx->actor);
        }
        break;
    }

    switch (ctx->step) {
    case 1:
        func_001C1550(ctx->actor, ctx->axes, ctx->request);
        if (ctx->actor->x148 == ctx->x68) {
            switch (ctx->x30) {
            case 1:
            case 2:
                if (ctx->x30 == 1)
                    ctx->maximum = GMax(ctx->maximum, ctx->axes[1].weight);
                else
                    ctx->maximum = GMax(ctx->maximum, ctx->axes[0].weight);
                break;
            }
        }
        break;
    case 0:
        if (ctx->action == 3) {
            ACTOR *actor = ctx->actor;
            func_001AB308(actor, *(void **)((char *)actor + 0x1AE0), *(void **)((char *)actor + 0x1AE8), *(void **)((char *)actor + 0x1AF8), 5.0f, actor->x1650);
            func_001AB308(actor, *(void **)((char *)actor + 0x1ADC), *(void **)((char *)actor + 0x1AE4), *(void **)((char *)actor + 0x1AFC), 5.0f, actor->x1650 + 0x100);
            func_001B55A0(actor, actor->x1650, *(void **)((char *)actor + 0x1AF8));
            func_001B55A0(actor, actor->x1650 + 0x100, *(void **)((char *)actor + 0x1AFC));
        }
        break;
    }
}

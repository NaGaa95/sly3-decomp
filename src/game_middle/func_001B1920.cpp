// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of the hero's target-facing movement (Sly 3 port of the Sly 2 state machine func_00190520): picks the stick
// angle (pad object from func_00156998 or the actor's own), measures the direction to the target in the actor's frame, runs the
// 0..3 state machine (face / turn-away / slow / fast) and updates the blend weights and the steering curve slope.
// WORK.target (a copy of the target position) is stored but never read afterwards, as in the original.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *fn; };
struct PADOBJ { char pad0[8]; float amount; char pad0C[0x2C - 0xC]; VTE *vt; };
struct CURVE { char pad0[0x1C]; float value; char pad20[0x20]; float slope; };
struct ANIMATION { char pad0[0x64]; float gain; };
struct LINK { char pad0[4]; void *object; };
struct PT { char pad0[0xC]; VTE *vt; };
struct P {
    char pad0[0xC]; VTE *vt; char pad10[0x134 - 0x10]; PADOBJ *pad;
    char pad138[0x1BC - 0x138]; float angle;
    char pad1C0[0xF60 - 0x1C0]; char action[0x10]; char padF70[0x110C - 0xF70]; float stickAngle;
    char pad1110[0x113C - 0x1110]; CURVE *curve;
    char pad1140[0x19E8 - 0x1140]; int state; float changed; char pad19F0[4]; struct PT *target; float farTime; int previous;
    int flipped; LINK *link; char pad1A08[0x1A70 - 0x1A08]; float combined; char pad1A74[8]; float activeOnly; char pad1A80[8];
    float idle; char pad1A8C[8]; ANIMATION *animation; float speedBlend, activeBlend;
};
struct CLOCK { float time, dt; };
struct LM { float v[3]; };
extern "C" {
extern CLOCK D_0036BB98;
extern qword D_00317550;
extern PADOBJ D_0036E6D0;
extern float D_00322BA0, D_00322BA4, D_00322BA8, D_00322BAC;
extern LM D_00322BB0, D_00322BC0;
int func_00156998(P *);
float func_001B2038(P *);
float func_0011E3B8(float);
void func_0024E878(P *, float);
M3 *func_0011C8C0(M3 *out, qword axis, float g);
float func_002A3EE8(float, float);
void func_001ADDD0(P *, int, int);
void func_001B0FF0(P *);
void func_0023E228(void *);
void func_001BDA88(void *, int, int);
float func_0011E598(float, float, float, LM *, float *);
void func_00148938(ANIMATION *);
float func_0011E560(float, float);
float fabsf(float);
}

static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GFromVf(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline qword LengthDot(qword v)
{
    qword one, d, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword ScaleRecip(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword Normalized(qword diff, qword fallback)
{
    qword length = LengthDot(diff);
    if (GFromVf(length) < 0.0001f)
        return fallback;
    return ScaleRecip(diff, length);
}
static inline qword Local(const M3 &m, qword v)
{
    qword q, one, a, b, c;
    __asm__("vmul.xyzw %2,%5,%8\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\tvmul.xyzw %3,%6,%8\n\tvmul.xyzw %4,%7,%8\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\tvaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\tvaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
            : "=j"(q), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(v));
    return q;
}
static inline qword Velocity(P *p) { VTE &e = p->vt[38]; return ((qword (*)(void *))e.fn)((char *)p + e.d); }
static inline int Can(P *p, int mode) { VTE &e = p->vt[113]; return ((int (*)(void *, int))e.fn)((char *)p + e.d, mode); }
static inline int PadHeld(PADOBJ *pad) { VTE &e = pad->vt[1]; return ((int (*)(void *, unsigned, float))e.fn)((char *)pad + e.d, 0x400, 0.15f); }
static inline void PadClear(PADOBJ *pad) { VTE &e = pad->vt[2]; ((void (*)(void *, unsigned))e.fn)((char *)pad + e.d, 0x400); }
static inline float Clamp(float f, float low, float high) { if (f < low) return low; else if (f > high) return high; return f; }
struct WORK { U target; U direction; U local; M3 matrix; M3 returned; };
extern "C" void func_001B1920(P *p)
{
    WORK w;
    int near = 0, far = 0;
    PADOBJ *pad = func_00156998(p) ? &D_0036E6D0 : p->pad;
    float heading = func_001B2038(p);
    if (p->flipped)
        heading = func_0011E3B8(heading + 3.1415927f);
    func_0024E878(p, heading);
    float diff = func_0011E3B8(p->stickAngle - p->angle);
    if (pad->amount > 0.3f) {
        float d = fabsf(diff);
        if (d < 1.0471976f) { near = 1; p->farTime = D_0036BB98.time; }
        else if (d > 2.0943952f) { far = 1; p->farTime = D_0036BB98.time; }
    } else
        p->previous = -1;
    VTE &te = p->target->vt[36];
    qword reference = ((M4 *(*)(void *))te.fn)((char *)p->target + te.d)->r[3];
    w.target.q = reference;
    VTE &pe = p->vt[36];
    qword normal = Normalized(Sub(reference, ((M4 *(*)(void *))pe.fn)((char *)p + pe.d)->r[3]), D_00317550);
    w.direction.q = normal;
    func_0011C8C0(&w.returned, D_00317550, p->angle);
    w.matrix = w.returned;
    w.local.q = Local(w.matrix, w.direction.q);
    float angle = func_0011E3B8(func_002A3EE8(w.local.f[2], w.local.f[0]) - 1.5707964f);
    int next = p->state;
    switch (next) {
    case 0:
        if (far) next = 2;
        else if (near) { if (D_0036BB98.time - p->changed > 1.4f) { p->previous = 0; next = 1; } }
        else if (D_0036BB98.time - p->farTime > 0.25f) next = 1;
        break;
    case 2:
        if (near) next = 0;
        else if (far) { if (D_0036BB98.time - p->changed > 1.4f) { p->previous = 2; next = 1; } }
        else if (D_0036BB98.time - p->farTime > 0.25f) next = 1;
        break;
    case 1:
        if (near && p->previous != 0) { next = 0; p->previous = -1; }
        else if (far && p->previous != 2) { next = 2; p->previous = -1; }
        else if (fabsf(angle) < D_00322BA0) { int slow = GFromVf(LengthDot(Velocity(p))) < D_00322BA8; if (slow) next = 3; }
        break;
    case 3:
        if (near && p->previous != 0) { next = 0; p->previous = -1; }
        else if (far && p->previous != 2) { next = 2; p->previous = -1; }
        else if (fabsf(angle) > D_00322BA4) { int fast = GFromVf(LengthDot(Velocity(p))) > D_00322BAC; if (fast) next = 1; }
        break;
    }
    func_001ADDD0(p, 4, next);
    func_001B0FF0(p);
    if (p->link) func_0023E228(p->link->object);
    if (PadHeld(pad) && Can(p, 3)) {
        PadClear(pad);
        func_001BDA88(p->action, 0, 0);
    }
    if (p->state == 3) return;
    float activeTarget, speedTarget;
    switch (p->state) {
    case 0: activeTarget = 1.0f; speedTarget = 1.0f; break;
    case 2: activeTarget = 1.0f; speedTarget = 0.0f; break;
    case 1: activeTarget = 0.0f; if (p->speedBlend > 0.5f) speedTarget = 1.0f; else speedTarget = activeTarget; break;
    }
    p->activeBlend = func_0011E598(p->activeBlend, activeTarget, D_0036BB98.dt, &D_00322BB0, 0);
    p->speedBlend = func_0011E598(p->speedBlend, speedTarget, D_0036BB98.dt, &D_00322BC0, 0);
    float active = p->activeBlend, speed = p->speedBlend;
    float idle = 1.0f - active;
    float combined = active * speed;
    float activeOnly = active * (1.0f - speed);
    p->combined = combined; p->idle = idle; p->activeOnly = activeOnly;
    func_00148938(p->animation);
    float steering = Clamp(angle / 1.7f, -1.0f, 1.0f);
    float target = p->animation->gain * (steering + 1.0f);
    target *= 0.5f;
    p->curve->slope = func_0011E560((target - p->curve->value) / D_0036BB98.dt, 3.0f);
}

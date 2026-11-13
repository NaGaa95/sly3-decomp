// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// State setter of the actor reaction object (same class as func_001C3470 / func_001C2E78): ignores a repeated state, undoes
// the old state (-1: reset the two limb push vectors and clear the actor vector at 0x1A0, 7: release the attached sub-object, 3/11: clear the
// limb push), stops the actor's two animation channels, prepares the new state (state 9 turns towards the velocity unless the
// actor is already moving along its normal, which redirects it to state 10; 11 / 5 / 12 push the actor towards its owner; 4 / 13 and
// 1 / 2 align the heading with the matrix) and finally starts the state's animation (fallback slot 0 or 9) and notifies the actor.
// Source-shape notes: the two push vectors and the CLQ curve are function-local static consts and FLT_MAX is a pool literal, which
// gives the original .rodata order (0x323560 vectors, 0x323580 curve, 0x323590 FLT_MAX, 0x3235A0 jump table); the 2D length goes
// to the FPU through an mtc1 helper fed directly by the VU value (reload makes the qmfc2), which reproduces the schedule.
typedef unsigned long long qword __attribute__((mode(TI)));
struct VE { short delta, pad; void *fn; };
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct CLQ { float g0, g1, g2, gPad; } __attribute__((aligned(16)));
struct LM { float gMin, gMax; };
struct MAT { float m[3][4]; qword pos; };
struct PART { char pad0[0x20]; VECTOR vel; };
struct PARTREF { char pad0[0x60]; PART *part; };
struct LIMB { char pad0[0xA8]; PARTREF *ref; };
struct OBJ { char pad0[0xC]; VE *vt; };
struct SUB { char pad0[0xC]; VE *vt; };
struct ACTOR
{
    char pad0[0xC]; VE *vt;
    char pad10[0x140 - 0x10]; void *x140;
    char pad144[0x1A0 - 0x144]; VECTOR v1A0;
    char pad1B0[0x1BC - 0x1B0]; float heading; qword normal;
    char pad1D0[0x110C - 0x1D0]; float headingGoal;
    char pad1110[0x113C - 0x1110]; int anim113C; int anim1140;
    char pad1144[0x1AC0 - 0x1144]; LIMB *limbs[2];
};
struct COUNTER { int pad0; int state; float t1; float t2; };
struct ANIMSLOT { void *anim; int pad[3]; };
struct C
{
    ACTOR *actor; int state; float tState; char padC[0x14 - 0xC]; COUNTER counter; int x24; int x28; char pad2C[4];
    ANIMSLOT anims[14]; int pad110; SUB *sub;
};
struct CLOCK { float t; float dt; };
extern CLOCK g_clock;
extern LM D_00341FF0;
extern qword D_00317560;
extern "C" {
int func_0013B500(ACTOR *, int);
void func_001F4E70(void *);
void func_001F4E98(void *);
void func_0023B620(ACTOR *, int);
void func_00137628(int *);
void func_0023AC58(int *);
void func_00240DB0(ACTOR *);
void func_002BC760(COUNTER *, void *);
float func_001205C8(qword);
float func_0011E3B8(float);
void func_0024E878(ACTOR *, float);
void func_0024F0B0(ACTOR *);
OBJ *func_001F4A80(ACTOR *);
void func_0024E8E8(ACTOR *, qword);
float atan2f(float, float);
void func_00262770(SUB *, OBJ *);
void func_002643D0(SUB *, void *);
void func_0023DD40(ACTOR *);
int func_00136880(void *, int);
void func_00137588(void *, ACTOR *, float, float, int, int *);
void func_0023AAE8(int, ACTOR *, int, int, int *);
}
static inline void Call(ACTOR *a, int slot) { VE *v = &a->vt[slot]; ((void (*)(void *))v->fn)((char *)a + v->delta); }
static inline void CallSub(SUB *a, int slot) { VE *v = &a->vt[slot]; ((void (*)(void *))v->fn)((char *)a + v->delta); }
static inline qword Velocity(ACTOR *a) { VE *v = &a->vt[38]; return ((qword (*)(void *))v->fn)((char *)a + v->delta); }
static inline MAT *Matrix(ACTOR *a) { VE *v = &a->vt[36]; return (MAT *)((char *(*)(void *))v->fn)((char *)a + v->delta); }
static inline MAT *MatrixObj(OBJ *a) { VE *v = &a->vt[36]; return (MAT *)((char *(*)(void *))v->fn)((char *)a + v->delta); }
static inline void SetVector(ACTOR *a, int slot, qword q) { VE *v = &a->vt[slot]; ((void (*)(void *, qword))v->fn)((char *)a + v->delta, q); }
static inline void Clear(VECTOR &v) { float *f = &v.x; f[1] = f[2] = 0.0f; v.x = 0.0f; }
static inline float Dot(qword a, qword b)
{
    qword d, one; float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline float LenXY(qword v)
{
    qword d, l; float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline float GFromClq(const CLQ *pclq, float g) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static inline float GLimitLm(LM *plm, float g)
{
    float gMin = plm->gMin, gMax = plm->gMax;
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
union VU { qword q; float f[4]; };

extern "C" void func_001C21F0(C *p, int state)
{
    static const VECTOR s_vDown = { 0.0f, 0.0f, -750.0f, 0.0f };
    static const VECTOR s_vUp = { 0.0f, 0.0f, 500.0f, 0.0f };
    static const CLQ s_clq = { -1.0f, 0.004f, 0.0f, 0.0f };
    void *anim;
    int flags;
    if (state == p->state)
        return;
    switch (p->state)
    {
    case -1:
        if (func_0013B500(p->actor, 0x34))
        {
            ACTOR *a = p->actor;
            a->limbs[0]->ref->part->vel = s_vDown;
            a->limbs[1]->ref->part->vel = s_vDown;
        }
        Call(p->actor, 102);
        Clear(p->actor->v1A0);
        func_001F4E70(p->actor->x140);
        p->counter.t2 = 3.40282347e+38f;
        break;
    case 7:
        if (p->sub)
        {
            func_0023B620(p->actor, 0);
            CallSub(p->sub, 54);
        }
        break;
    case 3:
    case 11:
        if (func_0013B500(p->actor, 0x34))
            Clear(p->actor->limbs[0]->ref->part->vel);
        break;
    }
    anim = 0;
    flags = 1;
    func_00137628(&p->actor->anim113C);
    func_0023AC58(&p->actor->anim1140);
    switch (state)
    {
    case -1:
        if (func_0013B500(p->actor, 0x34))
        {
            ACTOR *a = p->actor;
            Clear(a->limbs[0]->ref->part->vel);
            Clear(a->limbs[1]->ref->part->vel);
        }
        func_001F4E98(p->actor->x140);
        p->counter.t2 = g_clock.t;
        func_00240DB0(p->actor);
        func_002BC760(&p->counter, 0);
        p->x28 = 0;
        break;
    case 9:
        if (Dot(Velocity(p->actor), p->actor->normal) > -250.0f)
            state = 10;
        else
        {
            VU vel;
            vel.q = Velocity(p->actor);
            float scale = GLimitLm(&D_00341FF0, GFromClq(&s_clq, LenXY(vel.q)));
            float d = func_0011E3B8(func_001205C8(vel.q) + 3.14159274f - p->actor->heading);
            func_0024E878(p->actor, p->actor->heading + d * scale);
            func_0024F0B0(p->actor);
        }
    case 10:
        flags = 0x21;
        anim = p->anims[state].anim;
        break;
    case 11:
        flags = 0x21;
        {
            qword pos = MatrixObj(func_001F4A80(p->actor))->pos;
            func_0024E8E8(p->actor, Sub(pos, Matrix(p->actor)->pos));
        }
    case 3:
        anim = p->anims[state].anim;
        if (func_0013B500(p->actor, 0x34))
            p->actor->limbs[0]->ref->part->vel = s_vUp;
        break;
    case 5:
    case 12:
        {
            qword pos = MatrixObj(func_001F4A80(p->actor))->pos;
            func_0024E8E8(p->actor, Sub(pos, Matrix(p->actor)->pos));
        }
        if (state == 12)
            flags = 0x21;
        anim = p->anims[state].anim;
        break;
    case 0:
    case 6:
    case 8:
        anim = p->anims[state].anim;
        break;
    case 4:
    case 13:
        SetVector(p->actor, 41, D_00317560);
        {
            MAT *m = Matrix(p->actor);
            func_0024E878(p->actor, atan2f(m->m[0][1], m->m[0][0]));
        }
        if (state == 13)
            flags = 0x21;
        p->actor->headingGoal = p->actor->heading;
        anim = p->anims[state].anim;
        break;
    case 1:
    case 2:
        flags = 0;
        {
            MAT *m = Matrix(p->actor);
            func_0024E878(p->actor, atan2f(m->m[0][1], m->m[0][0]));
        }
        p->actor->headingGoal = p->actor->heading;
        anim = p->anims[state].anim;
        break;
    case 7:
        if (p->sub)
        {
            ACTOR *a = p->actor;
            func_0023B620(a, 1);
            OBJ *o = func_001F4A80(a);
            if (o)
            {
                func_00262770(p->sub, o);
                func_002643D0(p->sub, (char *)o + 0x150);
            }
            CallSub(p->sub, 56);
        }
        flags = 9;
        anim = p->anims[state].anim;
        break;
    }
    func_0023DD40(p->actor);
    p->state = state;
    p->tState = g_clock.t;
    if (state == -1)
        return;
    if (!anim)
        anim = p->anims[state < 9 ? 0 : 9].anim;
    if (state >= 9)
        p->x24 = !func_00136880(anim, 0x32B);
    func_00137588(anim, p->actor, 0.0f, 1.0f, flags, &p->actor->anim113C);
    func_0023AAE8(0, p->actor, -1, 0, &p->actor->anim1140);
    Call(p->actor, 101);
}

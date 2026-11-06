// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Hit reaction of an actor (Sly 3 version of the Sly 2 hit handler): accepts a hit record `in` (mask bit 2) for the reaction object `p`,
// rejects it for guarded / delegating actors, converts the hit into damage (in->delta, divided by 3 for two states of the attacker), applies it
// through the actor's counter, notifies the actor and then switches on the hit kind (in->flags) to choose the reaction (member callbacks
// Reaction / Stop / Special / the shared finish callback at D_00323620) before emitting the hit effect at the actor's position.
// Source-shape notes: the member-pointer constants (null, Reaction, Special, Stop) and the 0x400 push vector are compiler-made .rodata in
// order of first use; the finish callback constant (0x323620) was already emitted by an earlier function of the original translation unit, so it
// is referenced as data here. Argument types of func_001738C0 come from attachment_creation_api.h (that makes the position / space loads schedule
// like the original).
#include "attachment_creation_api.h"
typedef unsigned long long qword __attribute__((mode(TI)));
struct C;
typedef void (C::*ACTION)();
struct VE { short delta, pad; void *fn; };
struct WIDGET { char pad0[0x138]; struct CNT *count; };
struct CNT { char pad0[8]; int c; };
struct LINK { char pad0[0x14]; struct ACTOR **first; };
struct ACTOR
{
    char pad0[0xC]; VE *vt;
    char pad10[0x130 - 0x10]; int id;
    char pad134[0x1E8 - 0x134]; LINK *link;
    char pad1EC[0x2C4 - 0x1EC]; int guard;
    char pad2C8[0x508 - 0x2C8]; int mode;
    char pad50C[0x514 - 0x50C]; int arg514;
    char pad518[0x112C - 0x518]; int state;
    char pad1130[0x127C - 0x1130]; WIDGET *widget;
};
struct HIT
{
    char pad0[0x14]; ACTOR *object; int arg18; char pad1C[4]; int flags; int delta;
    char pad28[0x40 - 0x28]; float v0, v1, v2; char pad4C[4]; int mask;
};
struct COUNTER { int pad0; int state; float t1; float t2; };
struct C
{
    ACTOR *actor; int kind; char pad8[0x14 - 8]; COUNTER counter; char pad24[0x10C - 0x24]; void *effect; void *output;
    void Reaction() __asm__("func_001C3AE8");
    void Stop() __asm__("func_001C3B30");
    void Special() __asm__("func_001C3BE0");
};
struct VEC4 { float x, y, z, w; };
struct CLOCK { float t; float dt; };
struct GAME { char pad[0x47C0]; void *space; };
extern CLOCK g_clock;
extern GAME D_00475480;
extern ACTION D_00323620;
extern qword D_00317560;
extern "C" {
int func_001A9478(GAME *, int);
int func_001A9600(GAME *, int);
int func_001C3FB0(C *, HIT *);
int func_001F43C8(ACTOR *);
void func_001F43D0(ACTOR *, int);
int func_00137588(void *, ACTOR *, float, float, int, void *);
void func_001F4DD8(ACTOR *, ACTOR *, int, float);
void func_002BC760(COUNTER *, HIT *);
void func_001C2E58(C *, ACTION);
void func_00155ED8(ACTOR *, int);
void func_001854C8(void *, int, ACTOR *);
int func_0013B500(ACTOR *, int);
int func_0013B868(ACTOR *);
void *func_002459F8(int);
void func_00244F08(void *, ACTOR *);
void func_001C3008(C *);
void func_001C21F0(C *, int);
void func_001C3CD0(C *);
void func_00240CB0(int, int, int, int, int, int, qword, qword, int);
extern char D_0036C700[];
}
static inline int Reject(ACTOR *a, int flags) { VE *v = &a->vt[80]; return ((int (*)(ACTOR *, int))v->fn)((ACTOR *)((char *)a + v->delta), flags); }
struct MAT { AttachmentPackedPosition rows[4]; };
static inline MAT *Matrix(ACTOR *a) { VE *v = &a->vt[36]; return (MAT *)((char *(*)(void *))v->fn)((char *)a + v->delta); }
static inline qword Velocity(ACTOR *a) { VE *v = &a->vt[38]; return ((qword (*)(void *))v->fn)((char *)a + v->delta); }
static inline void Notify(ACTOR *a, int n) { VE *v = &a->vt[99]; ((void (*)(void *, int))v->fn)((char *)a + v->delta, n); }
static inline void SetVector(ACTOR *a, int slot, qword q) { VE *v = &a->vt[slot]; ((void (*)(void *, qword))v->fn)((char *)a + v->delta, q); }
static inline float Z(qword q) { float f; float w; __asm__("pextuw %0, $zero, %1" : "=&r"(w) : "r"(q)); return w; }

extern "C" int func_001C3470(C *p, HIT *in)
{
    float zero;
    ACTOR *src;
    if (!(in->mask & 2))
        return 0;
    if (func_001A9478(&D_00475480, p->actor->id) && !func_001A9600(&D_00475480, p->actor->id))
        return 0;
    if (func_001C3FB0(p, in))
    {
        if ((unsigned)(p->kind - 9) < 5u)
            return 0;
        in->delta = func_001F43C8(p->actor);
        goto notify;
    }
    if (Reject(p->actor, in->flags))
        return 0;
    if (p->actor->mode == 1)
    {
        func_00240CB0((int)in->object, in->arg18, p->actor->arg514, in->flags, 10, 0, D_00317560, D_00317560, 0);
        return 0;
    }
    if (p->actor->guard)
        in->delta = 0;
    else if (p->counter.state == 1)
        in->delta = 0;
    if (in->flags == 0x100000)
    {
        zero = 0.0f;
        float f = (float)(func_001F43C8(p->actor) - in->delta);
        if (zero < f)
        {
            if (p->counter.state != 1)
            {
                p->counter.state = 0;
                p->counter.t1 = p->counter.t2 = g_clock.t;
            }
            func_001F43D0(p->actor, (int)f);
            if (p->effect)
                func_00137588(p->effect, p->actor, zero, 1.0f, 1, &p->output);
            func_001738C0(D_00475480.space, Matrix(p->actor)->rows[3], (int)p->actor);
            return 1;
        }
        in->flags = 0x200;
        float *v = &in->v0;
        v[1] = v[2] = zero;
        in->v0 = zero;
    }
    src = in->object;
    if (src)
    {
        if (func_0013B500(src, 0x59))
            src = *src->link->first;
    }
    if (func_0013B500(src, 0x3A))
    {
        if (src->state == 0xE || src->state == 0x10)
            in->delta /= 3;
    }
notify:
    func_001F4DD8(p->actor, in->object, in->flags, -3.40282347e+38f);
    func_002BC760(&p->counter, in);
    Notify(p->actor, 3);
    {
        WIDGET *widget = p->actor->widget;
        if (widget && (widget->count->c || func_001F43C8(p->actor) - in->delta <= 0))
            func_00155ED8(p->actor, 5);
    }
    func_001C2E58(p, 0);
    func_001F43D0(p->actor, func_001F43C8(p->actor) - in->delta);
    if (func_001F43C8(p->actor) > 0 && in->flags != 0x800000)
    {
        p->counter.state = 1;
        p->counter.t1 = g_clock.t;
    }
    switch (in->flags)
    {
    case 0x100:
    case 0x200:
    default:
        func_001C3008(p);
        if (Z(Velocity(p->actor)) > 400.0f)
        {
            int effect = -1;
            switch (func_0013B868(p->actor))
            {
            case 0x34: effect = 0x69; break;
            case 0x35: effect = 0x84; break;
            case 0x36: effect = 0x83; break;
            }
            ACTOR *actor = p->actor;
            void *created = func_002459F8(effect);
            func_00244F08(created, actor);
        }
        func_001C2E58(p, &C::Reaction);
        break;
    case 0x8000:
        func_001C21F0(p, 8);
        func_001C2E58(p, &C::Special);
        break;
    case 0x800:
    case 0x1000:
        SetVector(p->actor, 40, D_00317560);
        SetVector(p->actor, 41, D_00317560);
        func_001C21F0(p, in->flags == 0x800 ? 1 : 2);
        func_001C2E58(p, &C::Stop);
        break;
    case 0x2000:
        if (func_001F43C8(p->actor) > 0)
        {
            func_001C21F0(p, 3);
            func_001C2E58(p, D_00323620);
        }
        else
            func_001C21F0(p, 0xB);
        break;
    case 0x400:
        { static const VEC4 kDown = { 0.0f, 0.0f, -1000.0f, 0.0f }; SetVector(p->actor, 40, *(const qword *)&kDown); }
        if (func_001F43C8(p->actor) > 0)
            func_001C21F0(p, 4);
        else
            func_001C21F0(p, 0xD);
        break;
    case 0x4000:
        if (func_001F43C8(p->actor) > 0)
        {
            func_001C21F0(p, 5);
            func_001C2E58(p, D_00323620);
        }
        else
            func_001C21F0(p, 0xC);
        break;
    case 0x40:
        func_001C3008(p);
        func_001C2E58(p, &C::Reaction);
        break;
    case 0x800000:
        func_001C3CD0(p);
        break;
    }
    func_001738C0(D_00475480.space, Matrix(p->actor)->rows[3], (int)p->actor);
    func_001854C8(D_0036C700, 10, p->actor);
    return 1;
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Damage / hit message handler of an actor: filters the message (disabled actor, attacker immunity, per-kind
// masks), applies the kind-specific reaction, subtracts the damage and picks the outcome state; returns whether the
// message was consumed.
typedef int qword __attribute__((mode(TI)));
struct Mask { unsigned char bytes[16]; };
struct VT { short delta, pad; void *function; };
struct XF { char pad0[0x30]; qword pos; };
struct LIST { char pad0[0x20]; int mask; };
struct ENTRY { char pad0[0x30]; LIST *list; };
struct OWNER { void *id; };
struct LINK { char pad0[0x14]; OWNER *owner; };
struct SLOT { int value; char pad4[0xC]; };
struct ACTOR { char pad0[0x112C]; int state; char pad1130[0x1578 - 0x1130]; int x1578; };
struct ATTACKER { char pad0[0x1E8]; LINK *link; };
struct MSG;
struct ENTRY;
struct STATES { char bytes[0x28]; ENTRY *Find(int key) __asm__("func_002387A8"); void Transition(int state, MSG *msg) __asm__("func_00238610"); };
struct MSG { char pad0[0x14]; ACTOR *source; char pad18[8]; int kind; int amount; char pad28[0x28]; int flags; };
struct P {
    char pad0[0xC]; VT *vt; char pad10[4]; OWNER *owner; char pad18[0x130 - 0x18]; int disabled;
    char pad134[0x29C - 0x134]; STATES states; int invulnerable; char pad2C8[0x368 - 0x2C8];
    void *anim; void *animState; int x370, x374, x378; char pad37C[4]; float hitTime; char pad384[0x3AC - 0x384];
    ACTOR *target; char pad3B0[0x3D8 - 0x3B0]; void *targetState; char pad3DC[0x4C8 - 0x3DC]; int shielded;
    char pad4CC[0xAE0 - 0x4CC]; SLOT first[26]; SLOT second[26]; char padE20[0x1028 - 0xE20]; int health;
    void *hurtAnim; void *hurtState; char pad1034[0x112C - 0x1034]; int state;
};
extern char D_00475480[], D_0036C700[];
extern struct { char pad0[0x47B0]; void *effects; } D_00475480_fx __asm__("D_00475480");
extern ACTOR *D_00370AC0, *D_0038AE90;
extern void *D_00479C28, *D_00479C34;
extern const float D_003273D4;
extern struct CLOCK { float time, dt; } g_clock;
extern "C" {
int func_001A9478(void *, int);
void func_001F43D0(P *, int);
int func_001F43C8(P *);
int func_0013B500(void *, int);
int func_002533C0(P *, int);
void func_002514D8(P *, int);
void func_002566F0(void *, int);
void func_001F4DD8(P *, ACTOR *, int, float);
void func_00137588(void *, P *, int, void *, float, float);
Mask func_00252AD0(int);
int func_00255FE0(P *, ACTOR *, Mask);
int func_00255D78(P *, ACTOR *, const Mask *);
void *func_00255130(P *, const Mask *);
int func_0021F410(int);
void func_001738C0(void *, qword, P *);
void func_001E2910(ACTOR *, qword);
void func_001E29B0(ACTOR *, qword);
int func_00240DD8(int);
void func_001854C8(void *, int, P *);
}
static inline int Call(P *p, int slot, int arg) { VT *e = &p->vt[slot]; return ((int (*)(void *, int))e->function)((char *)p + e->delta, arg); }
static inline XF *Xf(P *p) { VT *e = &p->vt[36]; return ((XF *(*)(void *))e->function)((char *)p + e->delta); }
#define FIRST(p, i) (*(int *)((char *)(p) + ((i) << 4) + 0xAE0))
#define SECOND(p, i) (*(int *)((char *)(p) + ((i) << 4) + 0xC80))
extern "C" int func_00251C08(P *p, MSG *msg)
{
    if (p->disabled != -1 && func_001A9478(D_00475480, p->disabled))
        return 0;
    if (!(msg->flags & 0x3E))
        return 0;
    if (Call(p, 97, (int)msg)) {
        func_001F43D0(p, 0);
        msg->flags = 0x10;
        goto apply;
    }
    if (Call(p, 80, msg->kind))
        return 0;
    {
        void *owner = 0;
        if (func_0013B500(msg->source, 0x59)) {
            owner = ((ATTACKER *)msg->source)->link->owner->id;
            if (owner == p->owner->id)
                return 0;
        }
        if (owner && (func_0013B500(owner, 0x55) || func_0013B500(owner, 0x56)))
            goto shield;
    }
    if (func_002533C0(p, 5)) {
        ENTRY *entry = p->states.Find(0xCE);
        if (!(msg->flags & 0x10)) {
            int kind = msg->kind;
            int mask = p->x370;
            if (!(kind & mask))
                return 1;
            if (entry && (entry->list->mask & mask))
                return 1;
        }
    }
    if (func_002533C0(p, 6)) {
        if (!(msg->kind & p->x374))
            return 1;
    }
    if (func_002533C0(p, 7)) {
        ENTRY *entry = p->states.Find(0xD0);
        int mask = p->x378;
        if (!(msg->kind & mask))
            return 1;
        if (entry && (entry->list->mask & mask))
            return 1;
    }
shield:
    if (p->shielded) {
        if (msg->kind == 0x4000 || msg->kind == 0x2000) {
            p->states.Transition(0x12, msg);
            __asm__ __volatile__(""); // keeps this exit separate (no cross-jump)
            return 1;
        }
    }
apply:
    switch (p->state) {
    case 0x16:
        func_002514D8(p, -1);
        break;
    case 0x10:
    case 0xE:
        msg->flags = 0x10;
        break;
    }
    if (p->invulnerable)
        msg->amount = 0;
    if (p->target == msg->source)
        func_002566F0(p->targetState, 5);
    if (msg->kind == 0x80000 && (msg->flags & 2)) {
        func_001F4DD8(p, msg->source, 0x80000, D_003273D4);
        p->health -= msg->amount;
        if (p->health <= 0) {
            p->states.Transition(0xD, msg);
            __asm__ __volatile__(""); // keeps this exit separate (no cross-jump)
            return 1;
        }
        func_00137588(p->hurtAnim, p, 1, &p->hurtState, 0.0f, 1.0f);
        return 1;
    }
    if (msg->kind == 0x200000 && (msg->flags & 2)) {
        if (func_00255FE0(p, msg->source, func_00252AD0(6))) {
            int health = func_001F43C8(p) - msg->amount;
            func_001F43D0(p, 4 < health ? health : 5);
            if (msg->source != D_00370AC0 || !func_0021F410(0x1C))
                func_001738C0(D_00475480_fx.effects, Xf(p)->pos, p);
            func_001F4DD8(p, msg->source, msg->kind, D_003273D4);
            p->states.Transition(0x11, msg);
            __asm__ __volatile__(""); // keeps this exit separate (no cross-jump)
            return 1;
        }
    }
    if (msg->kind == 0x400000 && (msg->flags & 2)) {
        Mask mask = func_00252AD0(0x2A);
        if (func_00255D78(p, msg->source, &mask))
            msg->flags |= 0x20;
        else
            msg->flags |= 8;
        func_002514D8(p, 0xE);
    }
    if (msg->kind == 0x800000 && (msg->flags & 2)) {
        Mask mask = func_00252AD0(0x2A);
        if (func_00255D78(p, msg->source, &mask))
            msg->flags |= 0x20;
        else
            msg->flags |= 8;
        func_002514D8(p, 0xC);
    }
    {
        void *effects = 0;
        switch (msg->kind) {
        case 0x40000:
            effects = D_00479C34;
            break;
        case 0x4000:
            if (msg->source == D_00370AC0)
                break;
        default:
            effects = D_00479C28;
            break;
        }
        if (effects)
            func_001738C0(effects, Xf(p)->pos, p);
    }
    if (p->state == -1) {
        if (func_0013B500(msg->source, 0x3A) && msg->source->state == 0xC)
            func_002514D8(p, 0xC);
    }
    if (D_0038AE90) {
        switch (msg->kind) {
        case 0x20000:
            func_001E2910(D_0038AE90, Xf(p)->pos);
            break;
        case 0x40000:
            if (msg->source == D_0038AE90 && msg->source->x1578)
                func_001E29B0(D_0038AE90, Xf(p)->pos);
            break;
        }
    }
    func_001F43D0(p, func_001F43C8(p) - msg->amount);
    if (func_001F43C8(p) <= 0)
        msg->flags |= 0x10;
    else {
        Mask mask = func_00252AD0(0x2A);
        if (func_00255D78(p, msg->source, &mask))
            msg->flags |= 0x20;
    }
    if (msg->flags & 0x10) {
        func_001F4DD8(p, msg->source, msg->kind, D_003273D4);
        p->states.Transition(0x10, msg);
        __asm__ __volatile__(""); // keeps this exit separate (no cross-jump)
        return 1;
    }
    if (msg->flags & 0x20) {
        int first = FIRST(p, func_00240DD8(msg->kind));
        // zero-instruction copy: stops cse replacing `first` by -1 in the next compare (target compares s0)
        int m1 = -1;
        __asm__("" : "=r"(m1) : "0"(m1));
        if ((first == m1 && SECOND(p, func_00240DD8(msg->kind)) != first) ||
            (FIRST(p, func_00240DD8(msg->kind)) == -1 && !func_00255130(p, &(const Mask &)func_00252AD0(6))))
            msg->flags |= 8;
        else {
            func_001F4DD8(p, msg->source, msg->kind, D_003273D4);
            p->states.Transition(0xE, msg);
            __asm__ __volatile__(""); // keeps this exit separate (no cross-jump)
            return 1;
        }
    }
    if (msg->flags & 8) {
        func_001F4DD8(p, msg->source, msg->kind, D_003273D4);
        p->states.Transition(0xF, msg);
        __asm__ __volatile__(""); // keeps this exit separate (no cross-jump)
        return 1;
    }
    if (msg->flags & 4) {
        func_001F4DD8(p, msg->source, msg->kind, D_003273D4);
        func_00137588(p->anim, p, 1, &p->animState, 0.0f, 1.0f);
        p->hitTime = g_clock.time;
        func_001854C8(D_0036C700, 0xF, p);
        return 1;
    }
    return 0;
}

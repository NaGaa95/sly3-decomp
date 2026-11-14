// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0016E118: movement-state transition (leave the old state, enter the new one). Sly 2 counterpart: func_0017B1A8.
// The state is stored before the "stillness changed" notification and again after it; the target's request
// supplies a point/direction (func_0016D9F0) that drives the jump velocity and the motion job.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
union U { qword q; float f[4]; };
struct REQ { int flag; float along, up; int padC; qword point, direction; };
struct VT {
    char pad[0x120];
    short d120; short p122; M4 *(*pfn120)(void *);
    char pad128[0x140 - 0x128];
    short d140; short p142; void (*pfn140)(void *, qword);
    char pad148[0x368 - 0x148];
    short d368; short p36A; void (*pfn368)(void *, REQ *, float);
};
struct TUNE { char pad[0xD0]; float speed; };
struct GRP { char pad[0xA0]; void *space; };
struct A {
    char pad0[0xC]; VT *vt;
    char pad10[0x48 - 0x10]; GRP *first; GRP *second;
    char pad50[0xD8 - 0x50]; TUNE *tuning;
    char padDC[0x364 - 0xDC]; int attention;
    char pad368[0x10D0 - 0x368]; void *p10D0;
    char pad10D4[0x11B4 - 0x10D4]; A *owner;
};
struct DVT { char pad[0x20]; short d20; short p22; void (*pfn20)(void *); };
struct DL { char pad[0x18]; DVT *vt; float tEnd; };
struct EA { float g; };
struct CTL { int pad; void *curves; void *asega; };
struct CLOCK { float t; float dt; };
struct S {
    char pad0[0x10]; A *actor;
    char pad14[0x40 - 0x14]; CTL *control;
    char pad44[0x50 - 0x44]; int mode; float tMode; int pad58; A *target; int owned; DL *delta;
};
extern "C" {
extern CLOCK g_clock;
extern struct VQ { qword q; } D_00317550;
extern char D_00475480[];
extern char D_0036E740[];
void func_0023C4A0(A *, float);
void func_00137D08(void *, int, int, float, float);
void func_001309D8(DL **);
void func_0028F068(A *, GRP *, int);
void func_0013CD10(void *, A *);
void func_0023DF78(A *);
void func_00131610(S *, int);
void func_0016D9F0(S *, REQ *, qword *, qword *);
qword func_0028E910(void *, void *, qword);
qword func_0028E990(void *, void *, qword);
DL *func_00130348(A *, GRP *, void *, float, qword, qword);
void func_001305C8(DL *, qword, qword);
A *func_001F4AD0(void *, int);
void func_001A9058(char *, int, float);
EA *func_00136880(void *, int);
void func_001703C8(void *, A *, int);
void func_0016E118(S *p, int next);
}
/* VU float operands: one built in a GPR (mfc1), one moved straight into a VU register (qmtc2) */
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=rj"(q) : "f"(f)); }
};
struct VU_FLOATV {
    qword q;
    VU_FLOATV(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
static inline M4 *Matrix(A *a) { VT *v = a->vt; return v->pfn120((char *)a + v->d120); }
static inline void SetVelocity(A *a, qword q) { VT *v = a->vt; v->pfn140((char *)a + v->d140, q); }
static inline void Request(A *a, REQ *r, float g) { VT *v = a->vt; v->pfn368((char *)a + v->d368, r, g); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
/* a * sa.x + b * sb.x */
static inline qword Scale2(qword a, VU_FLOAT sa, qword b, VU_FLOATV sb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(sa.q), "j"(b), "j"(sb.q));
    return r;
}
static inline int Still(int m) { int f = 0; if (m == 4 || m == 5 || m == 0) f = 1; return f; }
void func_0016E118(S *p, int next)
{
    REQ req;
    U point, direction;
    if (next == p->mode) return;
    switch (p->mode) {
    case -1: func_0023C4A0(p->actor, p->actor->tuning->speed * 0.1f); break;
    case 3: if (next != -1) func_00137D08(p->control->asega, 0, 0, 0.0f, 1.0f); break;
    }
    if ((unsigned)p->mode < 2 && (unsigned)next >= 2) {
        func_001309D8(&p->delta);
        func_0028F068(p->actor, p->actor->first, 2);
        func_0028F068(p->actor, p->actor->second, 2);
    }
    int was = Still(p->mode), now = Still(next);
    if (was != now) {
        p->mode = next;
        func_0013CD10(D_00475480, p->actor);
        func_0023DF78(p->actor);
    }
    p->mode = next;
    p->tMode = g_clock.t;
    switch (next) {
    case -1:
        func_0023C4A0(p->actor, p->actor->tuning->speed * 10.0f);
        func_00131610(p, 1);
        break;
    case 0: {
        float duration = 0.6f;
        Request(p->target, &req, duration);
        func_0016D9F0(p, &req, &point.q, &direction.q);
        /* velocity = (point - position) / duration + up * 1750 */
        VU_FLOAT k(1.0f / 0.6f);
        qword goal = point.q;
        M4 *m = Matrix(p->actor);
        SetVelocity(p->actor, Scale2(Sub(goal, m->r[3]), k, D_00317550.q, VU_FLOATV(1750.0f)));
        GRP *first = p->actor->first;
        if (!p->delta) {
            float end = g_clock.t + duration;
            qword localPoint = func_0028E910(0, first->space, point.q);
            qword localDirection = func_0028E990(0, first->space, direction.q);
            p->delta = func_00130348(p->actor, first, 0, end, localPoint, localDirection);
        } else {
            p->delta->tEnd = g_clock.t + duration;
            qword localPoint = func_0028E910(0, first->space, point.q);
            qword localDirection = func_0028E990(0, first->space, direction.q);
            func_001305C8(p->delta, localPoint, localDirection);
            DL *dl = p->delta;
            dl->vt->pfn20((char *)dl + dl->vt->d20);
        }
        int owned = 0;
        if (req.flag) owned = p->target->owner == p->actor;
        p->owned = owned;
        if (p->actor->attention) {
            A *focus = func_001F4AD0(D_00475480, 0);
            if (focus && p->target == focus) func_001A9058(D_0036E740, 3, 0.15f);
        }
        break;
    }
    case 3: {
        EA *e = func_00136880(p->control->curves, 0x59);
        if (e) func_00137D08(p->control->asega, 0, 0, e->g, 1.0f);
        func_001703C8(p->actor->p10D0, p->target, 2);
        break;
    }
    case 4:
    case 5:
        if (p->mode == 4) {
            EA *e = func_00136880(p->control->curves, 0x2A6);
            if (e) func_00137D08(p->control->asega, 0, 0, e->g, 1.0f);
        }
        break;
    }
}

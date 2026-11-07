// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// func_00285C98 (agent A69): per-frame state machine of an actor with a target (0x204) and a partner object (0x208).
// States 1..5 are re-dispatched until the state stops changing (do/while on p->state); then state 3 moves the target
// towards the partner and state 5 moves the actor towards a point from func_0028E910 (func_00120C80 smoothing with the
// two rodata SMP tables, step = g_clock.dt), handing over through func_00287080 when it arrives; finally, in any state but
// -1/0/5, a 4 Hz scan (CTX scope, func_0025D0D8 + func_001CD098 line checks within 50) can drop the actor into state 3.
// Field names are ours. The SMP tables are defined here (placed by their bytes at 0x329690/0x3296A0).
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *pfn; };
struct LO { char pad0[0xC]; struct VTE *vt; };
struct A { char pad0[0x28]; unsigned long pad28 : 56; unsigned long b2F : 8; };
struct B { char pad0[0x18]; unsigned long grf; };
struct T { char pad0[0xC]; struct VTE *vt; char pad10[0xD4 - 0x10]; qword **ppq; char padD8[0x130 - 0xD8]; struct A *pa; struct B *pb; void *p138; char pad13C[0x150 - 0x13C]; qword pos150; int f160; };
struct P { char pad0[0xC]; struct VTE *vt; char pad10[0x134 - 0x10]; void *input; char pad138[0x198 - 0x138]; int state; float tState; char pad1A0[0x204 - 0x1A0]; struct T *target; struct LO *other; char pad20C[0x2E0 - 0x20C]; float tScan; };
struct CTX { int a[4]; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern float D_0036BB9C;
extern struct GAME D_00475480;
struct SMP { float a, b, c; };
static const struct SMP D_00329690 = { 10000.0f, 1000.0f, 0.15f };
static const struct SMP D_003296A0 = { 3000.0f, 1000.0f, 0.15f };

int func_001A7A80(void *handle, float limit, int mask);
void func_00286630(struct P *p, int state);
void func_00286B00(struct P *p, int state);
qword func_0028E910(void *p, int n, qword pos);
int func_001C8610(void *p);
qword func_00120C80(qword current, qword target, const void *table, int mode, float step);
void func_00287080(struct P *p, struct A *pa, struct B *pb, qword a, qword b);
void *__3CTX(struct CTX *);
void _$_3CTX(struct CTX *, int);
int func_00285BC8(void *, void *);
void func_0025D0D8(struct GAME *, qword, int (*)(void *, void *), void *, float, int *, void ***);
int func_001CD098(qword pos, void *so, int a, int b, int c, int d, void *out, float r);

#define VCALL(o, i) ((void *(*)(void *))(o)->vt[i].pfn)((char *)(o) + (o)->vt[i].delta)
#define POS(o) (*(qword *)((char *)VCALL(o, 36) + 0x30))
#define SETPOS(o, q) ((void (*)(void *, qword))(o)->vt[34].pfn)((char *)(o) + (o)->vt[34].delta, q)

static inline float Dist(qword a, qword b)
{
    qword d, one;
    float f;
    int n;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(n));
    return f;
}
static inline float Dist2(qword a, qword b)
{
    qword d, one;
    float f;
    int n;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=&j"(one));
    __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(n));
    return f;
}
#define FINACTIVE(t) (((t)->pb->grf & 0x80000) || !((t)->pa->b2F & 1) || !func_001C8610((t)->pa))

void func_00285C98(struct P *p)
{
    int state;
    do {
        float dt;
        state = p->state;
        dt = g_clock.t - p->tState;
        switch (state) {
        case 1:
            if (func_001A7A80(p->input, 0.15f, 0x40))
                func_00286630(p, 2);
            break;
        case 2: {
            struct T *t = p->target;
            if (t->pa) {
                qword pos = func_0028E910(t->p138, 0, t->pos150);
                if (Dist(POS(p), pos) < 200.0f)
                    func_00286630(p, 3);
                else
                    func_00286630(p, 4);
            } else if (t->f160 || func_001A7A80(p->input, 0.15f, 0x40) || 0.4f < dt)
                func_00286630(p, 3);
            break;
        }
        case 4:
            if (p->tState < g_clock.t - 0.7f || FINACTIVE(p->target))
                func_00286630(p, 3);
            else if (func_001A7A80(p->input, 0.15f, 0x40))
                func_00286630(p, 5);
            break;
        case 3: {
            qword pos = POS(p->other);
            if (Dist(pos, POS(p->target)) < 75.0f)
                func_00286630(p, 1);
            break;
        }
        case 5:
            if (FINACTIVE(p->target))
                func_00286B00(p, 3);
            break;
        }
    } while (p->state != state);

    switch (p->state) {
    case 3: {
        qword pos = POS(p->target);
        qword r = func_00120C80(pos, POS(p->other), &D_00329690, 0, D_0036BB9C);
        SETPOS(p->target, r);
        break;
    }
    case 5: {
        qword pos = POS(p);
        qword goal = func_0028E910(p->target->p138, 0, p->target->pos150);
        qword r = func_00120C80(pos, goal, &D_003296A0, 0, D_0036BB9C);
        SETPOS(p, r);
        if (Dist2(r, goal) < 0.0001f) {
            struct T *t = p->target;
            func_00287080(p, t->pa, t->pb, (*t->ppq)[7], *(qword *)VCALL(p, 36));
            func_00286630(p, 1);
        }
        break;
    }
    }

    switch (p->state) {
    case -1:
    case 0:
    case 5:
        return;
    }
    if (0.25f < g_clock.t - p->tScan) {
        struct CTX ctx;
        int c, i;
        void **a;
        char out[0x30];
        qword pos;
        p->tScan = g_clock.t;
        pos = POS(p);
        __3CTX(&ctx);
        func_0025D0D8(&D_00475480, pos, func_00285BC8, p, 50.0f, &c, &a);
        for (i = 0; i < c; i++) {
            if (func_001CD098(pos, a[i], 0x7FFFFFFF, 0, 0, 1, out, 50.0f)) {
                func_00286B00(p, 3);
                break;
            }
        }
        _$_3CTX(&ctx, 2);
    }
}

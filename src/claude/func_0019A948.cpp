// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// AI state machine update: run the current state's transition rules until the state settles.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *(*method)(void *); };
struct XF { char pad[0x30]; qword q; };
struct ACTOR { char pad[0xC]; struct VTE *vt; };
struct H { char pad[0x30]; void *x30; char p34[0x44 - 0x34]; void *x44; char p48[0x50 - 0x48]; int x50; char p54[0x5C - 0x54]; int x5C;
    char p60[0x70 - 0x60]; int x70; };
struct STATE { int kind; void *obj; int pad8; int padC; } __attribute__((aligned(16)));
struct C { char pad0[0x10]; struct ACTOR *actor; int pad14; struct H *helper; char pad1C[0x30 - 0x1C]; struct STATE state;
    float started; float expires; };
struct CLOCK { float t; };
extern "C" {
extern struct CLOCK g_clock;
extern char D_00475480[];
void func_002389A0(struct C *p);
int func_00238AA8(struct C *p);
int func_00238AD0(struct C *p);
int func_0019AF68(struct C *p);
int func_0019AED0(struct C *p);
int func_0019AF20(struct C *p);
int func_0019AF98(struct C *p, struct STATE *ps);
int func_0019AEF8(struct C *p);
void func_0019A2D0(struct C *p, struct STATE *ps);
int func_0019B208(struct STATE *pa, struct STATE *pb);
void func_0019AD90(struct C *p);
void *func_00256090(struct ACTOR *a, void *old);
void func_001A6B00(struct H *h, void *o);
void *func_00173E00(void *g, int n, qword q, struct ACTOR *a);
void func_001739A8(void *o);
void func_00255AE0(struct ACTOR *a, int n);
// memset under another name so the 16-byte aligned clear stays a call (not the builtin sq expansion)
void *Memset(void *, int, unsigned int) __asm__("memset");

}
static __inline__ void Clear(struct STATE *ps) { Memset(ps, 0, sizeof(*ps)); }
#define VCALL(po, n) ((struct XF *)(po)->vt[n].method((char *)(po) + (po)->vt[n].delta))

static __inline__ int FContinue(struct C *p)
{
    if (func_0019AF68(p) && p->state.kind != 19) {
        switch (p->state.kind) {
        case 1: case 2: case 3: case 4: case 8: case 10: case 12: case 14: case 15: {
            struct STATE s;
            Clear(&s);
            s.kind = 19;
            func_0019A2D0(p, &s);
            break;
        }
        }
    }
    return !func_00238AA8(p);
}

extern "C" void func_0019A948(struct C *p)
{
    func_002389A0(p);
    while (FContinue(p)) {
        struct STATE prev = p->state;
        struct STATE next;
        switch (p->state.kind) {
        case 0: {
            Clear(&next);
            next.kind = 1;
            func_0019A2D0(p, &next);
            break;
        }
        case 1: case 14: case 15: {
            void *o;
            next = p->state;
            if (func_0019AED0(p)) next.kind = 12;
            else if (func_0019AF20(p)) next.kind = 18;
            else if (func_0019AF98(p, &next)) ;
            else if ((o = func_00256090(p->actor, 0))) {
                next.obj = o;
                next.kind = 2;
            } else if (p->state.kind == 15 && g_clock.t < p->expires) next.kind = 15;
            else if (func_0019AEF8(p)) next.kind = 14;
            else next.kind = 1;
            func_0019A2D0(p, &next);
            break;
        }
        case 2:
            next = p->state;
            if (func_0019AED0(p)) next.kind = 12;
            else if (func_0019AF20(p)) next.kind = 18;
            else if (func_0019AF98(p, &next)) ;
            else {
                struct H *h = p->helper;
                void *old = h->x44;
                void *o = func_00256090(p->actor, old);
                if (o != old) func_001A6B00(h, o);
                else if (func_00238AD0(p)) next.kind = 1;
            }
            func_0019A2D0(p, &next);
            break;
        case 3:
            next = p->state;
            if (func_0019AED0(p)) next.kind = 12;
            else if (func_00238AD0(p)) {
                next.kind = 4;
                next.obj = p->state.obj;
            }
            func_0019A2D0(p, &next);
            break;
        case 4:
            next = p->state;
            if (func_0019AED0(p)) next.kind = 12;
            else if (func_0019AF20(p)) next.kind = 18;
            else if (func_00238AD0(p)) next.kind = 1;
            else func_0019AF98(p, &next);
            func_0019A2D0(p, &next);
            break;
        case 12:
            next = p->state;
            if (!func_0019AED0(p)) next.kind = 1;
            func_0019A2D0(p, &next);
            break;
        case 8:
            if (func_00238AD0(p)) {
                void *o = func_00173E00(D_00475480, 0, VCALL(p->actor, 0x24)->q, p->actor);
                    Clear(&next);
                next.kind = 2;
                next.obj = o;
                func_0019A2D0(p, &next);
                func_001739A8(o);
            }
            break;
        case 7:
            if (func_00238AD0(p)) {
                struct H *h = p->helper;
                if (h->x50 != -1) {
                    if (h->x50 == 3) func_0019AD90(p);
                } else {
                    func_00255AE0(p->actor, h->x5C);
                    if (p->state.kind == 7) func_0019AD90(p);
                }
            }
            break;
        case 23:
            if (func_00238AD0(p)) {
                struct H *h = p->helper;
                if (h->x70)
                    func_0019AD90(p);
                else {
                            Clear(&next);
                    next.kind = 4;
                    next.obj = h->x30;
                    func_0019A2D0(p, &next);
                }
            }
            break;
        case 5: case 6: case 9: case 10: case 16: case 17: case 18: case 19: case 21:
            if (func_00238AD0(p)) func_0019AD90(p);
            break;
        case 22:
            if (func_00238AD0(p)) func_0019AD90(p);
            break;
        case 11: case 13: case 20:
            break;
        }
        if (func_0019B208(&p->state, &prev)) break;
    }
}
// The unit's next .rodata literal (FLT_MAX, used by func_0019AD90) shares the jump tables' 16-byte padded block.
extern "C" const float D_00321EAC;
const float D_00321EAC = 3.40282346638528859812e+38f;

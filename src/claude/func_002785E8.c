// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_002255C8 (the position query became a virtual call).
typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x80]; qword v; };
struct P { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct P *(*pf)(void *); };
struct B { int a[3]; struct VTE *vt; };
struct O { char pad[0xD8]; struct T *t; };
struct Q { int a; struct O *o; };
struct S { int a[3]; struct VTE *vt; char pad[0x1D0 - 0x10]; struct B *x; };
extern qword D_00317560;
extern char D_003292A0[], D_003292B0[];
void func_00244828(struct O *o, qword v);
void func_0023F180(struct O *o, qword v, void *a, qword b, void *c);
static inline struct P *Pos(struct B *b)
{
    return b->vt[36].pf((char *)b + b->vt[36].d);
}
void func_002785E8(struct S *p, struct Q *q)
{
    struct O *o = q->o;
    union { qword q; float f[4]; } u;
    qword r, v;

    float m = -1.0f;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(m));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(o->t->v), "j"(s));
    u.q = s;
    func_00244828(o, r);
    if (p->x) v = Pos(p->x)->q30; else v = Pos((struct B *)p)->q30;
    func_0023F180(o, v, D_003292A0, D_00317560, D_003292B0);
}

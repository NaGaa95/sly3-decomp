// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00278AC8: segment lengths along a path (zero-insn volatile asm keeps the then-arm store out of the jump delay slot).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct P { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct O { int a[3]; struct VTE *vt; };
struct R { struct VTE *vt; };
struct RV { struct VTE *vt; };
struct C { int x0; struct RV *x4; };
struct G { char pad[0x64]; float g64; };
struct W { char pad[0x1E74]; struct G *x1E74; };
struct E { struct O *o; int n; };
struct S { char pad[0x54]; int n54; struct E a58[1]; char pad1[0x264 - 0x60]; float g264; int pad2; struct O *x26C; struct O *x270; };
extern struct W *D_00370AC0;
extern char D_00475480[];
void func_001C7DC8(struct S *p);
struct C *func_00136EE0(struct G *g, struct W *w, int a, int b);
struct O *func_0017E1B8(void *game, int kind, int id, void *context);
static inline struct P *Pos(struct O *o)
{
    return o->vt[36].pf((char *)o + o->vt[36].d);
}
static inline int Dist2DBits(qword a, qword b)
{
    qword d, l;
    int f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "+j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(l));
    return f;
}
static inline float Dist2D(qword a, qword b)
{
    qword d, l;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "+j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(l));
    return f;
}
void func_00278AC8(struct S *p)
{
    struct G *g;
    int i;
    func_001C7DC8(p);
    g = D_00370AC0->x1E74;
    if (g) {
        float one = 1.0f;
        struct C *c = func_00136EE0(g, D_00370AC0, 1, 1);
        VU a, b;
        ((void (*)(void *, float, float, VU *, int))c->x4->vt[3].pf)((char *)c->x4 + c->x4->vt[3].d, 0.0f, one, &a, 0);
        ((void (*)(void *, float, float, VU *, int))c->x4->vt[3].pf)((char *)c->x4 + c->x4->vt[3].d, g->g64, one, &b, 0);
        *(int *)&p->g264 = Dist2DBits(a.q, b.q);
        __asm__ __volatile__("");
    } else {
        p->g264 = 200.0f;
    }
    for (i = 1; i < p->n54; i++) {
        qword pa = Pos(p->a58[i - 1].o)->q30;
        qword pb = Pos(p->a58[i].o)->q30;
        p->a58[i].n = Dist2D(pa, pb) / p->g264 + 0.5f;
    }
    p->x26C = func_0017E1B8(D_00475480, 5, 0x280, 0);
    p->x270 = func_0017E1B8(D_00475480, 5, 0x281, 0);
    p->x26C->vt[9].pf((char *)p->x26C + p->x26C->vt[9].d);
    p->x270->vt[9].pf((char *)p->x270 + p->x270->vt[9].d);
}

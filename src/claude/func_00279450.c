// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct O { int a[3]; struct VTE *vt; };
struct X { int a[3]; struct VTE *vt; char pad[0x260 - 0x10]; qword q260; };
struct E { struct O *o; int x4; };
struct S { char pad[0x48]; struct X *x48; char pad2[0x58 - 0x4C]; struct E a58[(0x278 - 0x58) / 8]; int n278; };
void func_00198D78(qword *v, int a, int b, float f, float g);
static inline struct P *Pos(void *o)
{
    struct O *b = o;
    return b->vt[36].pf((char *)b + b->vt[36].d);
}
static inline float Dist2D(qword a, qword b)
{
    qword d, l;
    float f;
    int t;
    __asm__("vsub.xyzw %0, %2, %1" : "=j"(d) : "j"(b), "j"(a));
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "+j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(f), "=&r"(t) : "j"(l));
    return f;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
void func_00279450(struct S *p, int k)
{
    struct { float f[4]; } v;
    struct { float f[4]; } home;
    register qword t asm("$2") = Pos(p->a58[p->n278 - 1].o)->q30; /* pin: target loads to v0 then copies */
    qword pos;
    *(qword *)&home = t;
    __asm__("" :: "r"(t)); /* zero-insn keep-alive: home store issues before the pos copy */
    pos = t;
    if (k != 0 || 50.0f < Dist2D(*(qword *)&home, Pos(p->x48)->q30)) {
        struct X *x;
        *(qword *)&v = pos;
        func_00198D78((qword *)&v, 0, 0, 100.0f, -350.0f);
        x = p->x48;
        x->vt[34].pf((char *)x + x->vt[34].d, Sub(*(qword *)&v, x->q260));
    }
}

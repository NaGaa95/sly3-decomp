// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct O;
struct M { short delta, pad; qword (*fn)(void *); };
struct VT { char pad[0x130]; struct M m; };
struct O { char pad[0xC]; struct VT *vt; };
struct P { char pad[0x10]; struct O *po; char pad1[0x30 - 0x14]; int x30; char pad2[0x40 - 0x34]; qword v40; };
extern qword D_00317550;
qword func_0023ED38(struct O *po);
void func_00244828(struct O *po, qword v);
static inline qword Method(struct O *po) { struct M *m = &po->vt->m; return m->fn((char *)po + m->delta); }
static inline float Y(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulX(qword a, qword b) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Splat(float g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float Len(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(d));
    return f;
}
static inline qword DivX(qword a, qword b)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(b), "j"(a));
    return r;
}
int func_00135B88(struct P *p)
{
    U s;
    float vy, l;
    qword d, up;
    switch (p->x30) {
    case 0:
    case 1:
    vy = Y(Method(p->po));
    if (vy < 0.0f) {
        float k;
        vy = vy * vy;
        k = -Y(func_0023ED38(p->po)) * 6.25e-6f;
        s.q = Splat(k * vy);
        func_00244828(p->po, MulX(D_00317550, s.q));
    }
    {
    qword a = p->v40;
    d = Sub(a, Method(p->po));
    }
    up = D_00317550;
    { qword t = Dot(d, up); __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(t) : "0"(t), "j"(up)); d = Sub(d, t); }
    l = Len(d);
    if (1e-4f < l) {
        float g = GMin(l, 5000.0f);
        qword n;
        s.q = Splat(l);
        n = DivX(d, s.q);
        s.q = Splat(g);
        func_00244828(p->po, MulX(n, s.q));
    }
    return 1;
    }
    return 0;
}

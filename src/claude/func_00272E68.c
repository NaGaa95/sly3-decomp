// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct P { char pad[0x10]; qword q10; };
struct VTE { short d; short pad; struct P *(*pf)(void *); };
struct X { int a[3]; struct VTE *vt; };
struct S { void *x0; int x4; char pad[8]; int x10; char pad2[0xF0 - 0x14]; qword qF0; };
struct T { qword v0; qword v10; char pad[0x54 - 0x20]; int x54; };
extern int D_00370AC0;
extern qword D_00317560;
struct X *func_001F4A80(void *p);
static inline qword VuFloat(float g)
{
    qword q;
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(g));
    return q;
}
static inline qword AddScaled(qword v, qword n, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(v), "j"(n), "j"(s));
    return r;
}
static inline float Len(qword v)
{
    qword d, one, l;
    float f;
    int t;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(f), "=&r"(t) : "j"(l));
    return f;
}
static inline qword DivQ(qword v, qword l)
{
    qword r;
    __asm__ __volatile__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline qword NormalizeSafe(float lf, qword l, qword v, qword def)
{
    if (lf < 0.0001f)
        return def;
    return DivQ(v, l);
}
void func_00272E68(struct S *p, struct T *t)
{
    struct X *x = func_001F4A80(p->x0);
    qword d = x->vt[36].pf((char *)x + x->vt[36].d)->q10;
    if (p->x10 == D_00370AC0) {
        t->x54 = 0;
    } else {
        VU h;
        h.q = VuFloat(-150.0f);
        t->v0 = AddScaled(t->v0, d, h.q);
    }
    switch (p->x4) {
    case 4: case 5: case 6: {
        VU w, h2;
        qword n, d2, one, l, z, hq;
        qword *pv = &t->v10;
        float lf;
        register int tmp asm("$3"); // pin: v1 for the lane temp
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(w.q) : "j"(p->qF0), "j"(t->v0));
        w.f[2] = 0.0f;
        hq = VuFloat(300.0f);
        h2.q = hq;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d2), "=&j"(one) : "j"(w.q));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d2));
        __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(lf), "=&r"(tmp) : "j"(l));
        n = NormalizeSafe(lf, l, w.q, D_00317560);
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(*pv) : "j"(n), "j"(hq));
        break;
    }
    }
}

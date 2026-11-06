// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct T *(*pf)(void *); };
struct O { int a[3]; struct VTE *vt; };
struct S { int x0; int x4; char pad[0x20]; float f28; char pad2[0xF0 - 0x2C]; qword qF0;
           char pad3[0x10]; qword q110; qword q120; float f130; float f134; int x138; };
extern struct CLOCK { float t; } g_clock;
static inline float Dist(qword a, qword b)
{
    qword d, one, l;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(l));
    return f;
}
void func_00273030(struct S *p, struct O *o)
{
    switch (p->x4) {
    case 4: case 5: case 6: {
        struct T *t = o->vt[36].pf((char *)o + o->vt[36].d);
        qword a = t->q30;
        qword b = p->qF0;
        float d = Dist(b, a);
        p->q120 = a;
        p->q110 = b;
        p->f130 = g_clock.t;
        p->x138 = 1;
        p->f134 = d / p->f28;
    }
    }
}

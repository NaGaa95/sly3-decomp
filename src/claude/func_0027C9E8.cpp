// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; qword (*pf)(void *); };
struct N { char pad[0x40]; qword q40; };
struct S { int a[3]; VTE *vt; char pad[0x40]; N *x50; };
struct T { char pad[0x10]; qword q10; };
extern "C" void func_001F3D48(S *p, T *t);
struct VU_FLOAT { qword qw; };
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    int t;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(t) : "j"(d));
    return g;
}
static inline qword AddScaled(qword v, qword n, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(v), "j"(n), "j"(s.qw));
    return r;
}
extern "C" void func_0027C9E8(S *p, T *t)
{
    func_001F3D48(p, t);
    qword v = p->vt[38].pf((char *)p + p->vt[38].d);
    qword n = p->x50->q40;
    float d = Dot(v, n);
    if (d < 0.0f)
        v = AddScaled(v, n, VuFloat(-d));
    t->q10 = v;
}

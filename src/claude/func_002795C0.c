// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct T *(*pf)(void *); };
struct O { int a[3]; struct VTE *vt; };
struct S { char pad[0x48]; int x48; char pad2[0x268 - 0x4C]; float f268; };
qword func_00250600(int x);
static inline float Dist(qword a, qword b)
{
    qword d, one, l;
    float f;
    register int t __asm__("$3"); /* pin: lane scratch in v1, keeps v0 for the result */
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(f), "=&r"(t) : "j"(l));
    return f;
}
int func_002795C0(struct S *p, struct O **ppo)
{
    qword v = func_00250600(p->x48);
    struct O *po = *ppo;
    struct T *t = po->vt[36].pf((char *)po + po->vt[36].d);
    return Dist(v, t->q30) <= p->f268;
}

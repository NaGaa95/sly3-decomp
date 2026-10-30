// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* func_00134148 / func_00134200: is the distance between the owner's position and another object's position below
   the near limit (g344) / above the far limit (g348)? Positions come from the vtable slot 36 accessor. */
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct XF { char pad[0x30]; qword pos; };
struct O { char pad[0xC]; struct VTE *vt; };
struct A { char pad[0xC]; struct VTE *vt; char pad2[0x344 - 0x10]; float g344; float g348; };
struct S { char pad[0x10]; struct A *pa; };
static __inline__ struct XF *Xf(struct O *po)
{
    return ((struct XF *(*)(void *))po->vt[36].pfn)((char *)po + po->vt[36].d);
}
static __inline__ float Dist(qword a, qword b)
{
    qword d, m, one, l;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(m), "=j"(one) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(m));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
int func_00134148(struct S *p, struct O *po)
{
    qword a = Xf((struct O *)p->pa)->pos;
    return Dist(a, Xf(po)->pos) < p->pa->g344;
}
int func_00134200(struct S *p, struct O *po)
{
    qword a = Xf((struct O *)p->pa)->pos;
    return p->pa->g348 < Dist(a, Xf(po)->pos);
}

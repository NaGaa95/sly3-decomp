// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_002240B0.
typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct P *(*pf)(void *); };
struct S { int a[3]; struct VTE *vt; char pad[0x130 - 0x10]; int k; int x134; int x138; char pad2[0x14C - 0x13C];
           struct S *pt; float r; char pad3[0x180 - 0x154]; int x180; int x184; };
void func_0023C660(struct S *p);
void func_00277208(struct S *p, int a, int b);
void func_00241100(struct S *p, int a, int b, int c, struct S *q);
static inline struct P *Pos(struct S *p)
{
    return p->vt[36].pf((char *)p + p->vt[36].d);
}
static inline float Dist(qword a, qword b)
{
    qword d, one, l;
    float f;
    register int t __asm__("$3"); /* pin: lane scratch in v1, keeps v0 for the flag */
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(one));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(f), "=&r"(t) : "j"(l));
    return f;
}
void func_00277030(struct S *p)
{
    func_0023C660(p);
    if (p->k == 1 && p->x138 != -1)
        func_00277208(p, p->x180, p->x184);
    if (p->pt) {
        qword a = Pos(p)->q30;
        qword b = Pos(p->pt)->q30;
        int f = p->r < Dist(a, b);
        if (f)
            func_00241100(p, 2, 0, 1, p);
    }
}

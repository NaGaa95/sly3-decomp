// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* step the 3-state machine; while following (state 1) push the target along its horizontal velocity toward us */
/* Sly 3 order: Sub before the dt qmtc2, whose asm carries a "memory" clobber so the a restore schedules first. */
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct XF { char pad[0x30]; qword pos; };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x218 - 0x10]; int x218; };
struct P { char pad[0x10]; struct O *po; char pad2[0x30 - 0x14]; int state; int pad34; struct O *p38; char pad3[0x40 - 0x3C]; qword v40; };
extern int D_0036BB9C;
extern qword D_00317550;
void func_002389A0(struct P *p);
int func_00238AD0(struct P *p);
void func_00135A50(struct P *p, int state);
qword func_001205F0(qword v, float g);
void func_0024E8E8(struct O *po, qword v);
static __inline__ struct XF *Xf(struct O *po)
{
    return ((struct XF *(*)(void *))po->vt[36].pfn)((char *)po + po->vt[36].d);
}
static __inline__ qword Qmtc2(int n)
{
    qword v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v) : "r"(n) : "memory");
    return v;
}
static __inline__ qword Sub(qword a, qword b)
{
    __asm__("vsub.xyzw %0, %0, %1" : "+j"(a) : "j"(b));
    return a;
}
static __inline__ qword Div(qword a, qword g)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(a), "j"(g));
    return r;
}
static __inline__ qword Dot(qword a, qword b)
{
    qword m, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(m), "=j"(one) : "j"(a), "j"(b));
    return m;
}
static __inline__ qword MulX(qword a, qword s)
{
    __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(s) : "j"(a));
    return s;
}
static __inline__ float Length(qword v)
{
    qword m, one, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(m), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(m));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
void func_00135888(struct P *p)
{
    int state;
    func_002389A0(p);
    do {
        state = p->state;
        switch (state) {
        case 0:
            if (func_00238AD0(p))
                func_00135A50(p, 1);
            break;
        case 1:
            if (p->po->x218)
                func_00135A50(p, 2);
            break;
        case 2:
            if (func_00238AD0(p))
                func_00135A50(p, -1);
            break;
        }
    } while (state != p->state);
    if (state == 1) {
        qword a = Xf(p->p38)->pos;
        qword v, z, b;
        union { qword q; float f[4]; } u;
        b = Xf(p->po)->pos;
        v = Sub(a, b);
        u.q = Qmtc2(D_0036BB9C);
        v = Div(v, u.q);
        z = D_00317550;
        v = Sub(v, MulX(z, Dot(v, z)));
        p->v40 = v;
        v = func_001205F0(v, 1000.0f);
        p->v40 = v;
        if (5.0f < Length(v))
            func_0024E8E8(p->po, v);
    }
}

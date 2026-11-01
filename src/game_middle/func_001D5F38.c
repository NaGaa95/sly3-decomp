// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Steers the actor along its path curve (same routine as Sly 2 func_001B1160): current curve picked by x200, back to the previous mode when off the curve ends.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct VT { short d; short pad; void *pfn; };
struct CURVE;
struct P { char pad0[0xC]; struct VT *vt; char pad1[0x14C - 0x10]; struct CURVE *p14C; struct CURVE *p150; float g154; float g158;
    char pad2[0x1AC - 0x15C]; float g1AC; float g1B0; char pad3[0x200 - 0x1B4]; int x200; };
extern qword D_00317530;
struct SPACE;
void func_0022EA50(struct CURVE*,qword,struct SPACE*,qword*,qword*,float*,float*,float);
float func_0022DFF0(struct CURVE *p, float g);
float func_0022DFA0(struct CURVE *p);
float func_0022DFC0(struct CURVE *p);
void func_0022E148(struct CURVE*,float,qword*,qword*);
void func_001D6110(struct P *p, int n);
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    {
    qword r;
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(r) : "j"(l));
    return r;
    }
}
void func_001D5F38(struct P *p)
{
    struct CURVE *q;
    float g, t;
    VU upos;
    switch (p->x200) {
    case 1:
        q = p->p14C;
        g = p->g1AC;
        break;
    case 4:
        q = p->p150;
        g = p->g1B0;
        break;
    default:
        q = 0;
        break;
    }
    if (!q)
        return;
    {
        struct VT *vt = &p->vt[36];
        upos.q = ((qword *(*)(void *))vt->pfn)((char *)p + vt->d)[3];
    }
    func_0022EA50(q,upos.q,0,0,0,&p->g154,0,p->g154);
    t = func_0022DFF0(q, p->g154 + p->g158);
    if (t < func_0022DFA0(q) || func_0022DFC0(q) < t) {
        if (p->x200 == 1)
            func_001D6110(p, 2);
    } else {
        VU v, uc, ur, ub;
        qword d, c, l, n, b, r;
        qword k;
        float gl;
        register int lengthBits __asm__("$3"); // register pin: the length bits go to $v1, $v0 keeps the fallback vector
        func_0022E148(q,t,&v.q,0);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v.q), "j"(upos.q));
        k = D_00317530;
        __asm__("vmove.xyzw %0, %1" : "=j"(c) : "j"(d));
        uc.q = c;
        l = VLen(uc.q);
        __asm__("qmfc2.ni %0,%2\n\tmtc1 %0,%1" : "=&r"(lengthBits), "=f"(gl) : "j"(l));
        if (gl < 1e-4f) {
            n = k;
        } else {
            __asm__ __volatile__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(n) : "j"(d), "j"(l));
        }
        __asm__("qmtc2.ni %1, %0" : "=j"(b) : "r"(g));
        ub.q = b;
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(n), "j"(ub.q));
        ur.q = r;
        {
            struct VT *vt = &p->vt[40];
            ((void (*)(void *, qword))vt->pfn)((char *)p + vt->d, ur.q);
        }
    }
}

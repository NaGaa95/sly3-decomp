// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_00225660 (change state; pick the nearest eligible actor).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct PO { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; qword (*pfn)(void *, ...); };
struct VTP { short d; short pad; PO *(*pfn)(void *); };
struct O { int a[3]; VTE *vt; char pad1[0x29C - 0x10]; char a29C[0x11D8 - 0x29C]; void *x11D8; int pad2; float f11E0; };
struct P;
struct N { P *owner; O *object; N *next; };
struct P { int a[3]; VTE *vt; char pad[0x130 - 0x10]; int k; char pad1[0x1D0 - 0x134]; O *x1D0; O *po; N hook; };
extern "C" {
extern char D_00475480[];
void func_002811F0(O *po, N *node);
void *func_002387A8(void *pv, int k);
void func_0016D840(void *pv, int k);
void func_0012F4F8(void *pv, qword q);
void func_00277F20(P *p, int k);
int func_0017E208(void *pg, int a, int b, int c, int cMax, O **apo);
int func_002513D0(O *po, int k);
void func_002811C8(O *po, N *node);
void func_002558A8(O *po, int k);
}
static inline PO *Pos(void *o)
{
    O *b = (O *)o;
    VTP *vt = (VTP *)b->vt;
    return vt[36].pfn((char *)b + vt[36].d);
}
static inline qword Splat(float f)
{
    int t; qword q;
    __asm__("mfc1 %0,%1" : "=r"(t) : "f"(f));
    __asm__("pextlw %0,%0,%0\n\tpextlw %1,%0,%0" : "+r"(t), "=r"(q));
    return q;
}
static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(t) : "j"(d));
    return g;
}
static inline qword PosQ(void *o) { return Pos(o)->pos; }
struct Vec { qword q; Vec(const qword &v) : q(v) {} operator qword() const { return q; } };
extern "C" void func_002786A0(P *p, int k)
{
    if (k == p->k)
        return;
    if (p->k == 5 && p->po) {
        void *pv;
        func_002811F0(p->po, &p->hook);
        pv = func_002387A8(p->po->a29C, 0xD9);
        if (pv)
            func_0016D840(pv, 2);
        if (p->po->x11D8)
            func_0012F4F8(p->po->x11D8, Splat(p->po->f11E0));
        p->po = 0;
    }
    func_00277F20(p, k);
    if (k == 5) {
        O *apo[0x20];
        int c, i;
        float gBest;
        O *poBest;
        Vec pos(p->x1D0 ? PosQ(p->x1D0) : PosQ(p));
        c = func_0017E208(D_00475480, 0x105, 0x3A, 0, 0x20, apo);
        gBest = 400.0f;
        poBest = 0;
        for (i = 0; i < c; i++) {
            O *po = apo[i];
            if (func_002513D0(po, 0xA)) {
                float g = GDist(Pos(po)->pos, pos);
                if (g < gBest) {
                    gBest = g;
                    poBest = po;
                }
            }
        }
        if (poBest) {
            VU u, v;
            qword q, s, r;
            p->po = poBest;
            p->hook.owner = p;
            p->hook.object = poBest;
            func_002811C8(poBest, &p->hook);
            q = poBest->vt[38].pfn((char *)poBest + poBest->vt[38].d);
            __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(q));
            __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(0.5f));
            u.q = q;
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(q), "j"(s));
            v.q = s;
            u.q = r;
            u.f[2] = 400.0f;
            ((void (*)(void *, qword))poBest->vt[40].pfn)((char *)poBest + poBest->vt[40].d, u.q);
            func_002558A8(poBest, 0);
        }
    }
}

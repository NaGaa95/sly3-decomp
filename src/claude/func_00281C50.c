// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_0022A060.
typedef int qword __attribute__((mode(TI)));
struct PP { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; int (*pfn)(); };
struct J { char pad[0xC]; struct VTE *vt; char pad1[0x33C - 0x10]; int x33C; };
struct P { char pad[0xC]; struct VTE *vt; char pad1[0x130 - 0x10]; int x130; int x134; float g138; float g13C; int x140; int x144; };
struct G { char pad[0x4044]; int x4044; };
extern struct G D_00475480;
void func_0023C660(struct P *p);
struct J *func_001F4AD0(struct G *pg, int k);
int func_0013B500(struct J *pj, int k);
static inline struct PP *Pos(void *o)
{
    struct J *b = o;
    return ((struct PP *(*)(void *))b->vt[36].pfn)((char *)b + b->vt[36].d);
}
static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
void func_00281C50(struct P *p)
{
    struct J *pj;
    int f;
    float r;
    func_0023C660(p);
    pj = func_001F4AD0(&D_00475480, 0);
    if (pj && func_0013B500(pj, p->x134)) {
        qword a;
        r = p->x144 ? p->g13C : p->g138;
        a = Pos(pj)->q30;
        __asm__("" : "+j"(a));
        f = GDist(a, Pos(p)->q30) < r;
    } else f = 0;
    if ((p->x130 == 0 || p->x130 == 2) && D_00475480.x4044)
        f = 0;
    if (f && func_0013B500(pj, 0x33) &&
        (pj->x33C != -1 || ((int (*)(void *))pj->vt[81].pfn)((char *)pj + pj->vt[81].d) == 2))
        f = p->x144;
    if (f != p->x144) {
        p->x144 = f;
        if (f)
            ((void (*)(void *, int, int, int, int, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
        else
            ((void (*)(void *, int, int, int, int, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 6, 0, 0, 0, 0);
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x20]; qword vel; qword pos; };
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct VT { char pad[0x120]; struct VTE e120; char pad128[0x300 - 0x128]; struct VTE e300; };
struct LO60 { char pad[0x60]; void *p60; };
struct OWNER { char pad[0xA4]; int nA4; };
struct GOBJ { char pad[0xDC]; struct LO60 *pDC; };
struct GEOM { struct OWNER *p0; struct GOBJ *p4; char pad8[0x84 - 8]; void *p84; char pad88[0xC0 - 0x88]; int nC0; };
struct P { char pad[0xC]; struct VT *pvt; char pad10[0x288 - 0x10]; void *p288; };
struct RES { qword pos; qword x10; union { qword q; float f[4]; } normal; qword x30; float g40; int x44; int n48; void *p4C; int pad50[4]; };
extern char D_00475480[];
void func_0023EDD0(struct P *p, struct GEOM *g, int a, int b, int c, int d);
int func_0013B500(void *object, int kind);
qword func_00250600(struct P *p);
qword func_00250648(struct P *p);
void func_0018B1E0(struct GEOM *g);
int func_00164A98(struct GEOM *g, void *pe, qword a, qword b, int c, struct RES *pres);
int func_0024EC28(struct P *p, qword position, struct GEOM *g, void *first);
void func_001CB8B0(void *pw, void *a, void *b, qword pos, qword dir, int k, int x, int y, int out, float g);
static inline qword Normalize(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("" : : "j"(v), "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(d));
    return g;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_0024EE30(struct P *p, struct GEOM *g, int a, int b, int c, int d)
{
    int grf;
    qword pos, v, dir, q;
    struct RES res;
    func_0023EDD0(p, g, a, b, c, d);
    grf = (int)p->pvt->e300.pfn((char *)p + p->pvt->e300.d);
    if (!(grf & 1)) return;
    if (func_0013B500(g->p4->pDC->p60, 0x32)) return;
    pos = ((struct XF *)p->pvt->e120.pfn((char *)p + p->pvt->e120.d))->pos;
    if (grf & 2) v = func_00250648(p);
    else v = func_00250600(p);
    if (g->nC0 != g->p0->nA4) func_0018B1E0(g);
    if (func_00164A98(g, g->p84, pos, v, 1, &res) <= 0) return;
    if (0.0f < res.g40) {
    if (!(grf & 8) && (0.7f < res.normal.f[2] || (!res.n48 && func_0024EC28(p, func_00250600(p), g, res.p4C))))
        dir = Normalize(((struct XF *)p->pvt->e120.pfn((char *)p + p->pvt->e120.d))->vel);
    else
        dir = res.normal.q;
    q = func_00250600(p);
    func_001CB8B0(D_00475480, p->p288, g, q, dir, 0xE, 0, 0, d, Dot(Sub(func_00250600(p), res.pos), dir));
    }
}

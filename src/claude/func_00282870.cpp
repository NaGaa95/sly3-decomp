// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct P { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct P *(*pf)(void *); };
struct R { char pad[0x164]; int x164; };
struct E { int id; int first; float g8; };
struct Q { char pad[0xC]; struct VTE *vt; char pad1[0x444 - 0x10]; float g444; };
struct S { char pad[0xC]; struct VTE *vt; char pad1[0x148 - 0x10]; struct S *x148; char pad2[0x198 - 0x14C]; int x198; int x19C; };
extern "C" {
extern struct CLOCK { float t; } D_0036BB98;
extern struct LM D_00341FF0;
extern qword D_00317550;
}
static const struct CLQ s_clq0 = { 1.0f, -0.5f, 0.0f, 0.0f };
static const struct CLQ s_clq1 = { 1.0f, -1.0f, 0.0f, 0.0f };
static const struct CLQ s_clq2 = { 0.5f, 0.0002857142826542258f, 0.0f, 0.0f };
static const struct LM s_lm = { 1.0f, 5.0f };
extern "C" {
struct R *func_00166540(struct Q *q);
struct E *func_00281E28(struct S *p, struct Q *q);
void func_00120A00(qword a, qword b, qword c, void *pa, void *pb, float *pu);
static __inline__ float GEvalClq(const struct CLQ *pclq, float g) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static __inline__ float GLimit(const struct LM *plm, float g)
{
    float lo = plm->gMin, hi = plm->gMax;
    float r;
    if (g < lo)
        r = lo;
    else if (hi < g)
        r = hi;
    else
        r = g;
    return r;
}
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j,!r"(q) : "r,m"(f)); } };
static inline qword AddScaled(qword v, qword n, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(v), "j"(n), "j"(s.q));
    return r;
}
}
#define POS(o) ((o)->vt[36].pf((char *)(o) + (o)->vt[36].d))
extern "C" int func_00282870(struct S *p, struct Q *q, float *pa, float *pb, float *pc)
{
    int mask = 0xFF;
    struct R *r = func_00166540(q);
    float g1, g2;
    if (r)
        mask = r->x164;
    if (!(mask & p->x19C))
        return 0;
    float gs = q->g444 + 10.0f;
    g1 = GLimit(&D_00341FF0, GEvalClq(&s_clq0, D_0036BB98.t - gs));
    gs = q->g444 + 0.1f;
    g2 = GLimit(&D_00341FF0, GEvalClq(&s_clq1, D_0036BB98.t - gs));
    if (p->x198) {
        g2 = 1.0f;
        g1 = g2;
    }
    if (g1 == 0.0f)
        return 0;
    {
        struct E *e = func_00281E28(p, q);
        qword a = POS(q)->q30;
        qword b;
        float t;
        if (p->x148) b = POS(p->x148)->q30; else b = POS(p)->q30;
        float u;
        func_00120A00(a, b, AddScaled(b, D_00317550, VU_FLOAT(e->g8)), 0, 0, &t);
        u = GLimit(&s_lm, GEvalClq(&s_clq2, t));
        if (pa) *pa = u;
        if (pb) *pb = g1;
        if (pc) *pc = g2;
    }
    return 1;
}

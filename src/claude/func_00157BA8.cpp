// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct GRF {
    union { unsigned int words[4]; unsigned char bytes[16]; };
    GRF operator&(const GRF &other) const {
        GRF result;
        for (int i = 0; i < 16; i++) result.bytes[i] = other.bytes[i] & bytes[i];
        return result;
    }
};
static inline int FUnequal(const GRF &a, const GRF &b)
{
    for (int i = 0; i < 16; i++) if (a.bytes[i] != b.bytes[i]) return 1;
    return 0;
}
struct CLQ { float g0, g1, g2, gPad; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE e120; };
struct SO { char pad[0xC]; VT *pvt; char pad1[0x2F4 - 0x10]; GRF grf; };
struct LIST { char pad[0x28]; int c; SO *a[1]; };
struct PO { char pad[0xC]; VT *pvt; char pad1[0x1160 - 0x10]; LIST *plist; };
struct P { char pad[0x10]; PO *p10; char pad2[0x30 - 0x14]; PO *p30; char pad3[0xA0 - 0x34]; SO *pA0; };
/* defined in order (not static) so they precede the FLT_MAX literal in .rodata, as in the target */
extern "C" const CLQ D_003206D0 = { -200.0f, 0.8f, 0.0f, 0.0f };
extern "C" const CLQ D_003206E0 = { 200.0f, 1.0f, 0.0f, 0.0f };
extern "C" const CLQ D_003206F0 = { -400.0f, 1.0f, 0.0f, 0.0f };
extern "C" {
extern GRF D_0036B320;
extern GRF D_00475440;
int func_002533C0(SO *p, int n);
LIST *func_00241AA0(PO *p);
SO *func_00157BA8(P *p);
}
static inline M4 *Matrix(void *pv)
{
    PO *p = (PO *)pv;
    VTE *e = &p->pvt->e120;
    return ((M4 *(*)(void *))e->pfn)((char *)p + e->d);
}
static inline float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    int n;
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(n) : "j"(d));
    return g;
}
/* Loop 1 reads the distance with a plain qmfc2 "=r" float output: reload then emits the mtc1 through spill reg v1,
   which advances reload's round-robin so loop 2's GRF copy gets a0/a1 as in the target. Loop 2 uses GDist. */
static inline float GDistR(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline float GFromClq(float g, const CLQ *pclq) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }

SO *func_00157BA8(P *p)
{
    SO *psoBest = 0;
    float gBest = 3.40282347e+38f;
    qword pos;
    LIST *plist;
    int i;
    Matrix(p->p10);
    pos = Matrix(p->p30)->r[3];
    plist = p->p10->plist;
    for (i = 0; i < plist->c; i++) {
        SO *pso = plist->a[i];
        float g;
        if (FUnequal(pso->grf & D_0036B320, D_00475440))
            continue;
        g = GDistR(pos, Matrix(pso)->r[3]);
        if (pso == p->pA0)
            g = GFromClq(g, &D_003206D0);
        if (func_002533C0(pso, 3))
            g = GFromClq(g, &D_003206F0);
        if (g < gBest) {
            gBest = g;
            psoBest = pso;
        }
    }
    plist = func_00241AA0(p->p30);
    if (plist) {
        for (i = 0; i < plist->c; i++) {
            SO *pso = plist->a[i];
            float g;
            if (FUnequal(pso->grf & D_0036B320, D_00475440))
                continue;
            g = GDist(pos, Matrix(pso)->r[3]);
            g = GFromClq(g, &D_003206E0);
            if (pso == p->pA0)
                g = GFromClq(g, &D_003206D0);
            if (func_002533C0(pso, 3))
                g = GFromClq(g, &D_003206F0);
            if (g < gBest) {
                gBest = g;
                psoBest = pso;
            }
        }
    }
    return psoBest;
}

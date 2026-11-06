// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int n[4]; } V;
typedef struct { V r[4]; } M4;
struct S { char pad[0x154]; int n154; char pad2[0x218 - 0x158]; int n218; char pad3[0x260 - 0x21C]; qword v260; };
void func_002BA818(V *pv, qword q);
void func_0023DA68(struct S *, void *, M4 *);
static inline qword Neg(qword v, V *k)
{
    qword s, r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(-1.0f));
    k->q = s;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(k->q));
    return r;
}
static inline qword MulPos(const M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
            : "=j"(r) : "j"(v), "j"(m->r[0].q), "j"(m->r[1].q), "j"(m->r[2].q), "j"(m->r[3].q));
    return r;
}
void func_0024F6F8(struct S *p, void *x, M4 *m)
{
    M4 loc;
    V k;
    func_002BA818(&loc.r[3], MulPos(m, Neg(p->v260, &k)));
    loc.r[0] = m->r[0];
    loc.r[1] = m->r[1];
    loc.r[2] = m->r[2];
    loc.r[2].n[3] = 0;
    loc.r[1].n[3] = 0;
    loc.r[0].n[3] = 0;
    loc.r[3].f[3] = 1.0f;
    func_0023DA68(p, x, &loc);
    p->n218 = 0;
    p->n154 = 1;
}

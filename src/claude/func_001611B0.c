// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct LO { char pad[0xC]; struct VEntry *table; char pad2[0x28 - 0x10]; unsigned long grf0 : 56; unsigned long grf1 : 8; };
struct S { char pad[0x10]; struct LO *plo; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
extern struct LO *D_00370AC0;
static const struct CLQ s_clq = { 800.0f, 0.075f, 0.0f, 0.0f };
static const struct LM s_lm = { 850.0f, 1100.0f };
#define GETPOS(o) (*(qword *)((char *)(o)->table[36].get((char *)(o) + (o)->table[36].delta) + 0x30))
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(d) : "j"(d));
    return d;
}
static __inline__ float GFromQ(qword v) { float g; int t; __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(t) : "j"(v)); return g; }
static __inline__ float GEvalClq(const struct CLQ *pclq, float g) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static __inline__ float GLimit(const struct LM *plm, float g)
{
    float lo = plm->gMin, hi = plm->gMax;
    if (g < lo) g = lo;
    else if (hi < g) g = hi;
    return g;
}

float func_001611B0(struct S *p)
{
    if (D_00370AC0 && (D_00370AC0->grf1 & 1)) {
        qword a = GETPOS(p->plo);
        float d = GFromQ(Len(Sub(a, GETPOS(D_00370AC0))));
        float g = GEvalClq(&s_clq, d);
        return GLimit(&s_lm, g);
    }
    return 850.0f;
}

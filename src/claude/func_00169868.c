// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct LO { char pad[0xC]; struct VEntry *table; };
struct X { char pad[0x20]; float g20, g24, g28; };
struct S { char pad[0x130]; struct LO *p130; struct LO *p134; struct LO *p138; char pad2[4]; struct X *p140; float t144; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
static const struct CLQ s_clq = { -0.05f, 0.00025f, 0.0f, 0.0f };
static const struct LM s_lm = { 0.0f, 4.0f };
void func_0023C660(struct S *p);
int func_00169808(struct LO *p);
void func_00169A30(struct S *p);
#define VCALL0(o, i) ((void (*)(void *))(o)->table[i].get)((char *)(o) + (o)->table[i].delta)
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
static __inline__ void SetG(struct X *px, float g) { float *pf = &px->g20; pf[2] = g; pf[1] = g; pf[0] = g; }

void func_00169868(struct S *p)
{
    func_0023C660(p);
    if (p->p130 && p->p134) {
        qword a;
        float d, g;
        if (func_00169808(p->p130) || func_00169808(p->p134)) {
            SetG(p->p140, 1e-4f);
            if (p->p138)
                VCALL0(p->p138, 9);
        } else {
            SetG(p->p140, 1.0f);
            if (p->p138)
                VCALL0(p->p138, 8);
        }
        a = GETPOS(p->p134);
        d = GFromQ(Len(Sub(a, GETPOS(p->p130))));
        g = GLimit(&s_lm, GEvalClq(&s_clq, d));
        if (g_clock.t - p->t144 > g)
            func_00169A30(p);
    }
}

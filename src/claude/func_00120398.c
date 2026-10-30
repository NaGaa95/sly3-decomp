// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the matched Sly 2 source src/hand/func_0011E7C8.c (Sly 3 addresses; this unit builds with -Os).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_00317530;
void func_00120200(qword a, qword b, qword c, qword pos, float *puv, float *pdist, qword *pnormal);
static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (g > hi)
        return hi;
    return g;
}
static inline qword VF(float g)
{
    U s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    return s.q;
}
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static __inline__ float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
void func_00120398(qword a, qword b, qword c, qword pos, float *puv, float *pdist, qword *pnormal)
{
    float v;
    qword w0, w1, w2, w3, n, l;
    qword *pdef;
    func_00120200(a, b, c, pos, puv, pdist, pnormal);
    puv[0] = GClamp(puv[0], 0.0f, 1.0f);
    v = GClamp(puv[1], 0.0f, 1.0f);
    puv[1] = v;
    w0 = VF(puv[0] - 1.0f);
    w1 = VF(-puv[0]);
    w2 = VF(1.0f - v);
    w3 = VF(v);
    __asm__("vmulax.xyzw $ACC, %5, %1x\n\tvmaddax.xyzw $ACC, %6, %2x\n\tvmaddax.xyzw $ACC, %7, %3x\n\tvmaddx.xyzw %0, %8, %4x"
            : "=j"(n) : "j"(w0), "j"(w1), "j"(w2), "j"(w3), "j"(a), "j"(b), "j"(c), "j"(pos));
    *pnormal = n;
    pdef = &D_00317530;
    l = Len(n);
    if (F(l) < 1e-4f) {
        *pnormal = *pdef;
    } else {
        qword r;
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(n), "j"(l));
        *pnormal = r;
    }
    { int nl; __asm__("qmfc2.ni %0, %1" : "=r"(nl) : "j"(l)); *(int *)pdist = nl; }
}

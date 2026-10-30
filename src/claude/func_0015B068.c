// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct V4 { float x, y, z, w; } __attribute__((aligned(16)));
static inline float Distance(qword a, qword b)
{
    qword d, one, l;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "0"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
float func_0015B068(qword pos, int n, struct V4 *v)
{
    float best = 3.402823466e+38f;
    int i;
    for (i = 0; i < n; i++, v++) {
        U t;
        float d;
        t.q = *(qword *)v;
        d = Distance(pos, t.q) * v->w;
        if (d < best)
            best = d;
    }
    return best;
}

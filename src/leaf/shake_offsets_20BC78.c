// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-strength-reduce
typedef int qword __attribute__((mode(TI)));
struct CLQ { float g0, g1, g2; };
struct LM { float gMin, gMax; };
struct ShakeSelf {
    unsigned char prefix0[0x90];
    qword velocity;
    unsigned char gapA0[0xD0 - 0xA0];
    float offset[3];
};
extern struct CLQ D_00325A10;
extern struct LM D_00341FF0;
float func_0011E940(float low, float high);
static inline float GEvalClq(const struct CLQ *pclq, float g) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static inline float GLimit(const struct LM *plm, float g)
{
    float lo = plm->gMin, hi = plm->gMax;
    if (g < lo)
        return lo;
    if (hi < g)
        return hi;
    return g;
}
static inline qword Length(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return d;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
// Randomize the three shake offsets within +-amplitude, where amplitude follows the speed of the owner velocity through a quadratic curve limited to [gMin,gMax] and scaled by 10.
void func_0020BC78(struct ShakeSelf *self)
{
    float amplitude = GLimit(&D_00341FF0, GEvalClq(&D_00325A10, F(Length(self->velocity)))) * 10.0f;
    int i;
    for (i = 0; i < 3; i++) {
        float *base = self->offset;
        float *slot = base + i;
        *slot = func_0011E940(-amplitude, amplitude);
    }
}

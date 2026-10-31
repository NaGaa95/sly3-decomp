// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct CurveClock { float now, step; };
struct CurveSelf {
    unsigned char prefix0[0x230];
    float start;
    unsigned char gap234[0x240 - 0x234];
    float coeff[3];
    unsigned char gap24C[0x250 - 0x24C];
    float lower, upper;
    unsigned char gap258[0x278 - 0x258];
    float offset;
};
extern struct CurveClock D_0036BB98;
qword func_001C9428(void *self, int zero, qword v);
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline float Eval(const float *c, float t)
{
    return c[0] + t * (c[1] + t * c[2]);
}
static inline float GClamp(float g, float lo, float hi)
{
    float result;
    if (g < lo)
        result = lo;
    else if (hi < g)
        result = hi;
    else
        result = g;
    return result;
}
qword func_002105B0(struct CurveSelf *self)
{
    float g = Eval(self->coeff, D_0036BB98.now - self->start);
    union { qword q; float f[4]; } v;
    v.q = Make(GClamp(g, self->lower, self->upper) + self->offset, 0.0f, 0.0f);
    return func_001C9428(self, 0, v.q);
}

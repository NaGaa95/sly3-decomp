// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"
struct Basis { qword rows[3]; };
struct SampleFrame {
    unsigned char prefix00[0x20];
    float radius[3];
    unsigned char gap2C[4];
    float alpha[3];
    unsigned char gap3C[4];
    unsigned char basis[0x30];
    qword position;
    unsigned char gap80[0xF0 - 0x80];
    void *object;
};
struct SampleResult {
    qword position;
    struct Basis basis;
    float alpha;
    float radius;
};
struct LM { float gMin; float gMax; };
extern struct LM D_00341FF0;
qword func_0028E910(void *source, void *destination, qword point);
void func_0028EA00(struct Basis *output, void *source, void *destination, void *orientation);
static inline float Eval(const float *c, float t)
{
    return c[0] + t * (c[1] + t * c[2]);
}
static inline float GClamp(float g, float gMin, float gMax)
{
    float result;
    if (g < gMin)
        result = gMin;
    else if (gMax < g)
        result = gMax;
    else
        result = g;
    return result;
}
void func_0020CC20(struct SampleFrame *self, void *unused_context, struct SampleResult *result, float time)
{
    struct Basis basis;
    result->position = func_0028E910(self->object, 0, self->position);
    func_0028EA00(&basis, self->object, 0, self->basis);
    result->basis = basis;
    result->alpha = GClamp(Eval(self->alpha, time), D_00341FF0.gMin, D_00341FF0.gMax);
    result->radius = Eval(self->radius, time);
}

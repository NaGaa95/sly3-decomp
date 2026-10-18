// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct BlendTimerObject { unsigned char prefix[0x160]; int word160, word164, word168; };
struct BlendTimerSelf {
    unsigned char prefix0[0xC0];
    float output;
    unsigned char gapC4[0x380 - 0xC4];
    int mode;
    unsigned char gap384[0x398 - 0x384];
    float duration;
    float timer;
    unsigned char gap3A0[0x414 - 0x3A0];
    struct BlendTimerObject *object;
};
struct BlendTimerClock { float now, step; };
struct LM { float gMin, gMax; };
extern struct BlendTimerClock D_0036BB98;
extern struct LM D_00341FF0;
extern float D_00325850[3], D_00325860[3];
extern qword D_00317560;
float func_002A3408(float x);
void func_00240DB0(void *owner);
float func_00280EA8(void *object, void *actor, int a, int b);
void func_00240CB0(void *self, int a, void *target, int b, int c, int d, qword e, qword f, int g);
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
void func_00207928(struct BlendTimerSelf *self)
{
    if (self->timer > 0.0f) {
        float remaining = self->timer - D_0036BB98.step;
        self->timer = remaining;
        if (remaining <= 0.0f) {
            self->timer = 0.0f;
            self->output = 0.0f;
            func_00240DB0(self);
        } else {
            float progress = 1.0f - remaining / self->duration;
            float wave = func_002A3408((self->duration - remaining) * 10.0f);
            float first = GClamp(Eval(D_00325850, progress), D_00341FF0.gMin, D_00341FF0.gMax);
            float second = GClamp(Eval(D_00325860, wave), D_00341FF0.gMin, D_00341FF0.gMax);
            self->output = first * second;
        }
    }
    if (self->mode != 4) {
        if (self->object) {
            if (0.5f <= func_00280EA8(self->object, self, 0, 0))
                func_00240CB0(self->object, 0, self, self->object->word160, self->object->word164, self->object->word168, D_00317560, D_00317560, 0);
        }
    }
}

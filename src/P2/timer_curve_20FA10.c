// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct TimerSelf {
    unsigned char prefix0[0xC0];
    float output;
    unsigned char gapC4[0x1BC - 0xC4];
    float duration;
    unsigned char gap1C0[0x1C8 - 0x1C0];
    float timer;
};
struct BlendTimerClock { float now, step; };
struct LM { float gMin, gMax; };
extern struct BlendTimerClock D_0036BB98;
extern struct LM D_00341FF0;
extern float D_00325B20[3], D_00325B30[3];
float func_002A3408(float x);
void func_00240DB0(void *owner);
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
void func_0020FA10(struct TimerSelf *self)
{
    if (self->timer > 0.0f) {
        float remaining = self->timer - D_0036BB98.step;
        self->timer = remaining;
        if (remaining <= 0.0f) {
            self->output = 0.0f;
            func_00240DB0(self);
        } else {
            float progress = 1.0f - remaining / self->duration;
            float wave = func_002A3408((self->duration - remaining) * 10.0f);
            float first = GClamp(Eval(D_00325B20, progress), D_00341FF0.gMin, D_00341FF0.gMax);
            float second = GClamp(Eval(D_00325B30, wave), D_00341FF0.gMin, D_00341FF0.gMax);
            self->output = first * second;
        }
    }
}

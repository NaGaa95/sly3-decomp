// SLY3_CFLAGS: -Os -G0
#include "approach_curve.h"
struct BlendOwner { unsigned char prefix[0x18]; unsigned int flags; };
struct BlendController { unsigned char bytes[0x11C0]; };
struct BlendSelf {
    unsigned char prefix0[0x130];
    int controller;
    struct BlendOwner *owner;
    unsigned char gap138[0x3A4 - 0x138];
    void *resource;
    unsigned char gap3A8[0x3E4 - 0x3A8];
    float next;
    unsigned char gap3E8[0x404 - 0x3E8];
    float blend;
    int saturated;
    int rumbling;
    float rumbleTime;
};
struct BlendClock { float now, step; };
extern struct BlendClock D_0036BB98;
extern const struct ApproachCurve D_00325760, D_00325770;
extern struct BlendController D_0036E740[];
static inline float Clamp(float x, float lower, float upper)
{
    float result = lower;
    if (!(x < lower)) {
        if (upper < x)
            result = upper;
        else
            result = x;
    }
    return result;
}
void func_00205418(struct BlendSelf *self);
void func_00207880(struct BlendSelf *self);
void func_001A9058(char *controller, int kind, float duration);
void func_00205238(struct BlendSelf *self)
{
    float target, value;
    const struct ApproachCurve *curve;
    if (!self->resource)
        return;
    if ((self->owner->flags & 8) && !self->saturated) {
        if (self->next < D_0036BB98.now)
            func_00205418(self);
        target = 1.0f;
        curve = &D_00325760;
    } else {
        target = 0.0f;
        curve = &D_00325770;
    }
    value = func_0011E598(self->blend, target, curve, 0, D_0036BB98.step);
    value = Clamp(value, 0.0f, 1.0f);
    self->blend = value;
    if (value == 1.0f)
        self->saturated = 1;
    else if (value < 0.8f)
        self->saturated = 0;
    func_00207880(self);
    if (0.7f < self->blend) {
        if (1.0f < D_0036BB98.now - self->rumbleTime) {
            func_001A9058((char *)&D_0036E740[self->controller], 0, 1.0f);
            self->rumbling = 1;
            self->rumbleTime = D_0036BB98.now;
        }
    } else {
        if (self->rumbling) {
            func_001A9058((char *)&D_0036E740[self->controller], 0, 0.01f);
            self->rumbling = 0;
            self->rumbleTime = 0.0f;
        }
    }
}

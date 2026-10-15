// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "animation_ensure_api.h"
struct RateInstanceView {
    unsigned char prefix[0x2C];
    struct RateInstanceView *next;
};
struct AnimationRateSetView {
    unsigned char prefix[0x40];
    struct RateInstanceView *first;
    unsigned char unused44[0x24];
    float rate;
};
struct AnimationSuppressionView { unsigned char prefix[0x58]; int enabled; };
struct AnimationRateScope { unsigned char unused_storage[16]; };
extern char D_00475480[];
void func_00138B88(void *, float);
void func_002BBEC8(void *, int);
int func_00138AC8(void *);
void func_001A93C8(void *, int, unsigned int);
void func_001A9420(void *, int, unsigned int);
void func_001376D0(struct ASEG *receiver, float rate)
{
    struct AnimationRateScope scope;
    struct AnimationRateSetView *animation = (struct AnimationRateSetView *)receiver;
    struct RateInstanceView *instance;
    for (instance = animation->first; instance; instance = instance->next)
        func_00138B88(instance, rate);
    animation->rate = rate;
    func_002BBEC8(&scope, 2);
}
void func_00138AF0(struct SeekRuntime *receiver, int enabled)
{
    struct AnimationSuppressionView *runtime = (struct AnimationSuppressionView *)receiver;
    if (func_00138AC8(receiver))
        return;
    if (enabled != runtime->enabled) {
        if (enabled)
            func_001A93C8(D_00475480, -1, 3);
        else
            func_001A9420(D_00475480, -1, 3);
        runtime->enabled = enabled;
    }
}

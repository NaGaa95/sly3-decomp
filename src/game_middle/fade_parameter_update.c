// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct FadeOwnerView {
    char prefix[0xC0];
    float value;
    char gap[0x184 - 0xC4];
    char *optional;
};
struct FadeContextView {
    struct FadeOwnerView *owner;
    int state;
    float started;
    char gap[0x18 - 0xC];
    int active;
    float wave_started;
    float fade_started;
};
struct S;
extern int func_0013B500(char *, int);
extern void func_0023DD40(struct S *);
extern float cosf(float);
extern float D_0036BB98;
extern float D_00323600[3], D_00323610[3], D_00341FF0[2];
static __inline__ float Polynomial(const float *coefficients, float value)
{
    return coefficients[0] + value * (coefficients[1] + value * coefficients[2]);
}
static __inline__ float Clamp(float value, float minimum, float maximum)
{
    if (value < minimum)
        return minimum;
    if (maximum < value)
        return maximum;
    return value;
}
void func_001C2CC0(struct FadeContextView *context)
{
    float duration;
    float parameter;
    float wave;
    if (context->owner->optional && func_0013B500(context->owner->optional, 0x60))
        duration = 1.0f;
    else
        duration = 0.5f;
    if (context->active != -1) {
        if (context->state == -1) {
            float elapsed = D_0036BB98 - context->fade_started;
            if (duration < elapsed) {
                context->active = -1;
                context->owner->value = 0.0f;
                func_0023DD40((struct S *)context->owner);
                return;
            }
            parameter = elapsed / duration;
        } else {
            parameter = 0.0f;
        }
        wave = cosf((D_0036BB98 - context->wave_started) * 10.0f);
        context->owner->value =
            Clamp(Polynomial(D_00323600, parameter), D_00341FF0[0], D_00341FF0[1]) *
            Clamp(Polynomial(D_00323610, wave), D_00341FF0[0], D_00341FF0[1]);
    }
}

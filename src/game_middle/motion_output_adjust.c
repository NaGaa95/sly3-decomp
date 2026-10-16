// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct MotionLimits { float minimum, maximum; };
struct MotionCurve { float value, first, second; };
struct MotionOutputContext {
    char prefix[0x28];
    int mode;
    char gap[0x13C - 0x2C];
    int override_parameters;
};
struct MotionOutput {
    char prefix[0x38];
    struct MotionLimits limits;
    char gap40[8];
    struct MotionCurve curve;
    char gap54[0x6C - 0x54];
    int flags;
};
extern struct MotionLimits D_00323320, D_00323338;
extern struct MotionCurve D_00323328, D_00323340;

void func_001BD758(struct MotionOutputContext *context, struct MotionOutput *output)
{
    if (context->override_parameters) {
        output->limits = D_00323320;
        output->curve = D_00323328;
        output->flags &= ~4;
    }
    switch (context->mode) {
    case 0:
        output->flags |= 1;
        break;
    case 2:
    case 3:
        output->limits = D_00323338;
        output->curve = D_00323340;
        output->flags = (output->flags & ~4) | 0x10;
        break;
    }
}

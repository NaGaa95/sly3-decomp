// Sly 2 CalculateEmitvx algorithm, adapted to the complete Sly 3 0x178C08 body.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ParticleLimits { float minimum, maximum; };
struct EmissionSampling { int count; float tilt_step, pan_step, tilt, pan; };
extern "C" float func_0011E3B8(float angle);
extern "C" float func_0011E940(float low, float high);
extern "C" void func_00178C08(int requested, ParticleLimits *limits,
    int maximum, EmissionSampling *sampling)
{
    int rows;
    float span;
    if (requested > 0)
        sampling->count = requested < maximum ? requested : maximum;
    else
        sampling->count = maximum;
    rows = (maximum + (sampling->count - 1)) / sampling->count;
    span = func_0011E3B8(limits->maximum - limits->minimum);
    sampling->pan_step = 6.2831855f / sampling->count;
    sampling->tilt_step = span / rows;
    sampling->tilt = limits->minimum + sampling->tilt_step * 0.5f;
    sampling->pan = func_0011E940(0.0f, 6.2831855f);
}

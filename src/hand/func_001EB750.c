// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original Sly 3 state and record semantics.
int func_001EB750(float value)
{
    if (value > 0.01f)
        return 0;
    if (value < -0.01f)
        return 1;
    return 2;
}

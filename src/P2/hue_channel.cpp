// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Original degree normalization and ordered piecewise hue channel.
extern "C" float func_0011F970(float lower, float upper, float degrees)
{
    while (degrees >= 360.0f)
        degrees -= 360.0f;
    while (degrees < 0.0f)
        degrees += 360.0f;
    if (degrees < 60.0f)
        return lower + (upper - lower) * degrees * (1.0f / 60.0f);
    if (degrees < 180.0f)
        return upper;
    if (degrees < 240.0f)
        return lower + (upper - lower) * (240.0f - degrees) * (1.0f / 60.0f);
    return lower;
}

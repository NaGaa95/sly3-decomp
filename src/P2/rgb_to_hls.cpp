// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Three scalar color components; output ordering is hue, lightness, saturation.
struct ColorComponents { float x, y, z; };
extern "C" void func_0011F770(ColorComponents *rgb, ColorComponents *hls)
{
    float r = rgb->x;
    float g = rgb->y;
    float b = rgb->z;
    float minimum;
    float maximum;
    if (r < g && r < b)
        minimum = r;
    else if (g < b)
        minimum = g;
    else
        minimum = b;
    if (g < r && b < r)
        maximum = r;
    else if (b < g)
        maximum = g;
    else
        maximum = b;
    float difference = maximum - minimum;
    float sum = maximum + minimum;
    float lightness = sum * 0.5f;
    if (difference == 0.0f) {
        hls->x = 0.0f;
        hls->y = lightness;
        hls->z = 0.0f;
        return;
    }
    float redDistance = (maximum - r) / difference;
    float greenDistance = (maximum - g) / difference;
    float blueDistance = (maximum - b) / difference;
    float saturation;
    if (lightness <= 0.5f)
        saturation = difference / sum;
    else
        saturation = difference / (2.0f - sum);
    // The original leaves hue unspecified if no component equals a NaN maximum.
    float hue;
    if (r == maximum)
        hue = (blueDistance + 6.0f - greenDistance) * 60.0f;
    if (g == maximum)
        hue = (redDistance + 2.0f - blueDistance) * 60.0f;
    if (b == maximum)
        hue = (greenDistance + 4.0f - redDistance) * 60.0f;
    while (hue >= 360.0f)
        hue -= 360.0f;
    while (hue < 0.0f)
        hue += 360.0f;
    hls->x = hue;
    hls->y = lightness;
    hls->z = saturation;
}

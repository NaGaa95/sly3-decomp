// Sample the object's piecewise-linear table at |angle|/pi (clamped by the shared limit), interpolating between neighbouring entries.
// SLY3_CFLAGS: -Os -G0 -ffast-math
struct Limit { float minimum, maximum; };
struct Curve {
    unsigned char opaque000[0x1E0];
    float samples[(0x214 - 0x1E0) / 4];
    int count;
};
extern struct Limit D_00341FF0;
float func_0011EE68(struct Limit *limit, float value);

float func_00219058(struct Curve *curve, float angle)
{
    int last = curve->count - 1;
    float u = func_0011EE68(&D_00341FF0, __builtin_fabsf(angle) * 0.31830987f);
    float step = 1.0f / (float)last;
    int index = (int)(u * (float)last);
    int next = index + 1 < last ? index + 1 : last;
    float frac = (u - (float)index * step) / step;
    return (1.0f - frac) * curve->samples[index] + frac * curve->samples[next];
}

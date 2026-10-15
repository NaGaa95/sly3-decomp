// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef float (*MinimumObjective)(void *, float);
struct MinimumSample { float x, value; };

static inline float Clamp(float x, float lower, float upper)
{
    if (x < lower) return lower;
    if (x > upper) return upper;
    return x;
}
static inline float Maximum(float a, float b) { return a < b ? b : a; }
static inline float Minimum(float a, float b) { return b < a ? b : a; }

extern "C" void func_0011EF00(MinimumObjective objective, void *context,
                             float initial, float step, float lower, float upper,
                             float tolerance, float *out_x, float *out_value)
{
    MinimumSample samples[5];
    int iteration;
    float position = Clamp(initial, lower, upper);

    samples[0].x = Maximum(lower, position - step);
    samples[0].value = objective(context, samples[0].x);
    samples[2].x = position;
    samples[2].value = objective(context, position);
    samples[4].x = Minimum(upper, position + step);
    samples[4].value = objective(context, samples[4].x);

    for (;;) {
        if (samples[0].value < samples[2].value) {
            samples[4] = samples[2];
            samples[2] = samples[0];
            samples[0].x = Maximum(lower, samples[2].x + samples[2].x - samples[4].x);
            samples[0].value = objective(context, samples[0].x);
        } else if (samples[4].value < samples[2].value) {
            samples[0] = samples[2];
            samples[2] = samples[4];
            samples[4].x = Minimum(upper, samples[2].x + samples[2].x - samples[0].x);
            samples[4].value = objective(context, samples[4].x);
        } else break;
    }

    for (iteration = 0; iteration < 10; ++iteration) {
        float left_width = samples[2].x - samples[0].x;
        float right_width = samples[4].x - samples[2].x;
        if (left_width < tolerance && right_width < tolerance) break;
        samples[1].x = left_width * 0.5f + samples[0].x;
        samples[1].value = objective(context, samples[1].x);
        samples[3].x = right_width * 0.5f + samples[2].x;
        samples[3].value = objective(context, samples[3].x);
        if (samples[1].value < samples[2].value) {
            if (samples[1].value < samples[3].value) {
                samples[4] = samples[2];
                samples[2] = samples[1];
            } else {
                samples[0] = samples[2];
                samples[2] = samples[3];
            }
        } else if (samples[2].value <= samples[3].value) {
            samples[0] = samples[1];
            samples[4] = samples[3];
        } else {
            samples[0] = samples[2];
            samples[2] = samples[3];
        }
    }
    if (out_x) *out_x = samples[2].x;
    if (out_value) *out_value = samples[2].value;
}

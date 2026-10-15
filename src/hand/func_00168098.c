// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct State { unsigned char pad[0x114]; float duration; } State;
// Report whether the scaled time has reached the threshold and optionally
// calculate its 400-unit transition weight.
int func_00168098(const State *state, float *weight, float scale, float threshold)
{
    float time = scale * state->duration;
    if (threshold < time) return 0;
    if (weight) {
        float start = threshold - 400.0f;
        if (start < time)
            *weight = (threshold - time) / (threshold - start);
        else
            *weight = 1.0f;
    }
    return 1;
}

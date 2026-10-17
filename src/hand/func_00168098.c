// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct State { unsigned char pad[0x114]; float duration; } State;
int func_00168098(const State *state, float scale, float threshold, float *weight)
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

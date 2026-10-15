// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ShaderFrameRange { float low, high; };
struct ShaderFrameUsers { void *first, *last; int memberOffset; };
struct ShaderFrameCycle {
    char prefix[0x1C];
    int frameCount;
    char pad20[0x38 - 0x20];
    ShaderFrameUsers users;
    char pad44[0x50 - 0x44];
    ShaderFrameRange speedRange, pauseRange;
    float speed, position, pauseDuration, pauseRemaining;
};
typedef char CheckShaderFrameCycle70[sizeof(ShaderFrameCycle) == 0x70 ? 1 : -1];
extern "C" int func_0011AEF8(void *);
extern "C" float func_0011E940(float, float);
extern "C" float func_0011EDB8(float, float);
extern "C" void func_00237220(ShaderFrameCycle *, int);
extern "C" float D_0036BB9C;

extern "C" void func_00237408(ShaderFrameCycle *state)
{
    if (func_0011AEF8(&state->users) || state->frameCount < 2) return;
    if (state->pauseRemaining > 0.0f) {
        state->pauseRemaining -= D_0036BB9C;
    } else {
        state->position += state->speed * D_0036BB9C;
        if ((float)state->frameCount <= state->position) {
            state->speed = (float)state->frameCount /
                func_0011E940(state->speedRange.low, state->speedRange.high);
            state->pauseRemaining = state->pauseDuration =
                func_0011E940(state->pauseRange.low, state->pauseRange.high);
        }
        state->position = func_0011EDB8(state->position, (float)state->frameCount);
        func_00237220(state, (int)state->position);
    }
}

extern "C" float func_002374F8(ShaderFrameCycle *state)
{
    float frames = (float)state->frameCount;
    float speed = state->speed;
    float position = state->position;
    float duration = state->pauseDuration;
    return (position / speed) / (frames / speed + duration);
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Historical EE GCC C++ minimum operators preserve the original floating-point bounds.
#include "m2c_prelude.h"
typedef struct State { u8 unknown0[0x14]; u8 offsets[4]; u8 unknown1[8]; f32 output[8]; f32 input[7]; f32 scale; } State;
static inline f32 ee_min(f32 left, f32 right) {
    return left <? right;
}
static inline f32 clamp(f32 value, f32 low, f32 high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}
extern "C" void func_00264F10(State *state) {
    f32 scale = state->scale * 0.007874016f;
    f32 alpha = scale * state->offsets[3];
    f32 red = ee_min(state->input[0] + state->offsets[0], 255.0f);
    f32 green = ee_min(state->input[1] + state->offsets[1], 255.0f);
    f32 blue = ee_min(state->input[2] + state->offsets[2], 255.0f);
    state->output[0] = red;
    state->output[1] = green;
    state->output[2] = blue;
    state->output[3] = state->input[3];
    state->output[4] = state->input[4];
    state->output[5] = state->input[5];
    state->output[6] = state->input[6];
    state->output[7] = clamp(alpha, 0.0f, 1.0f);
}

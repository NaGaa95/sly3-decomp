// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Update the pair of float thresholds when the linked state is enabled.
#include "m2c_prelude.h"
typedef struct EnabledState { u8 unknown[0xC]; s32 enabled; } EnabledState;
typedef struct ThresholdState { u8 unknown[0x138]; EnabledState *linked; u8 pad[0x34]; f32 first; f32 second; } ThresholdState;
void func_0014E770(ThresholdState *state, f32 value) {
 if (state->linked->enabled) { state->first = value; state->second = value - 5.0f; }
}

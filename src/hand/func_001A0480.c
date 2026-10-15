// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct State { u8 reserved[0x13C]; s32 first[2][5]; s32 second[2][5]; } State;
void func_001A0480(State *state, u32 group, s32 category, s32 amount) {
    if (category != -1 && category < 5 && group < 2U) {
        state->first[group][category] += amount;
        state->second[group][category] += amount;
    }
}

// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct State {
    u8 reserved[0x15C]; s32 fallback[32], preferred[32];
    s32 enabled; u8 reserved260[0x18]; s32 selected;
} State;
s32 func_00279660(State *state) {
    s32 value;
    if (state->enabled == 0 || (value = state->preferred[state->selected]) == -1)
        value = state->fallback[state->selected];
    return value;
}

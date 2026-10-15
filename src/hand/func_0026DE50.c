#include "m2c_prelude.h"
typedef struct State { u8 unknown[0x1A0]; f32 value; } State;
s32 func_0026DE50(State *state) {
    return 0.0f < state->value;
}

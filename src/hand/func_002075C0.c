// Original GCC member-pointer metadata proves the function boundary.
#include "m2c_prelude.h"
typedef struct State { u8 unknown[0x3C4]; u32 count; s32 entries[4]; } State;
void func_002075C0(State *state, s32 value) {
    if (state->count < 4) {
        state->entries[state->count++] = value;
    }
}

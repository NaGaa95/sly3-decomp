// Original GCC member-pointer metadata proves the function boundary.
#include "m2c_prelude.h"
typedef struct State { u8 unknown[0x44]; s32 count; s32 *entries; } State;
void func_001860D8(State *state, s32 value) {
    s32 count = state->count;
    if (count < 8) {
        state->entries[count] = value;
        state->count = count + 1;
    }
}

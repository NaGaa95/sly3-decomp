// Append to a bounded inline array; field offsets recovered from the original loads/stores.
#include "m2c_prelude.h"
typedef struct QueueState { u8 unknown_0[0x3CC]; u32 count; s32 entries[2]; } QueueState;
void func_00254400(QueueState *state, s32 arg1) {
    u32 count;
    count = state->count;
    if (count < 2) {
        state->entries[count] = arg1;
        state->count = count + 1;
    }
}

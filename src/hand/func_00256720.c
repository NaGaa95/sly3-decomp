// Append to a bounded inline array; field offsets recovered from the original loads/stores.
#include "m2c_prelude.h"
typedef struct QueueState { u8 unknown_0[0x1034]; s32 entries[8]; u32 count; } QueueState;
void func_00256720(QueueState *state, s32 arg1) {
    u32 count;
    if (arg1 != -1) {
        count = state->count;
        if (count < 8) {
            state->entries[count] = arg1;
            state->count = count + 1;
        }
    }
}

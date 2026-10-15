// Append to the bounded inline array of 32 entries.
#include "m2c_prelude.h"
typedef struct QueueState { u8 unknown[0x228]; u32 count; s32 entries[32]; } QueueState;
void func_00285590(QueueState *state, s32 value) {
    u32 count = state->count;
    if (count < 32) {
        state->entries[count] = value;
        state->count = count + 1;
    }
}

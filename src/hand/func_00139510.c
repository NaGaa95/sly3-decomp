// Append to the bounded inline array of four 32-bit entries.
#include "m2c_prelude.h"
typedef struct QueueState { u8 unknown[0x130]; u32 count; s32 entries[4]; } QueueState;
void func_00139510(QueueState *state, s32 value) {
    u32 count = state->count;
    if (count < 4) {
        state->entries[count] = value;
        state->count = count + 1;
    }
}

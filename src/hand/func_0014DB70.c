// Append to a bounded inline array; field offsets recovered from the original loads/stores.
#include "m2c_prelude.h"
typedef struct QueueState { u8 unknown_0[0x1C]; u32 count; s32 entries[3]; } QueueState;
void func_0014DB70(void *arg0, s32 arg1) {
    QueueState *state = M2C_FIELD(arg0, QueueState **, 0x138);
    u32 count;
    count = state->count;
    if (count < 3) {
        state->entries[count] = arg1;
        state->count = count + 1;
    }
}

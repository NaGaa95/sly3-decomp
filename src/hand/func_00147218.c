// Append an inline entry and update both associated counts.
#include "m2c_prelude.h"
typedef struct State { u8 unknown[0x4C8]; s32 entries[4]; u32 count; u32 limit; } State;
void func_00147218(State *state, s32 value) {
 u32 count = state->count;
 if (count < 4) { u32 next = count + 1; state->entries[count] = value; state->count = next; state->limit = next; }
}

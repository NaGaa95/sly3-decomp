// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"
typedef struct Record { s32 first, second, third, reset; s32 unknown[3]; } Record;
typedef struct State { u8 unknown[0x270]; Record rows[2][6]; u32 counts[2]; } State;
void func_00217F10(State *state, s32 group, s32 first, s32 second, s32 third) {
    u32 count = state->counts[group];
    if (count < 6) {
        Record *entry = &state->rows[group][count];
        state->counts[group] = count + 1;
        entry->first = first;
        entry->second = second;
        entry->third = third;
        entry->reset = 0;
    }
}

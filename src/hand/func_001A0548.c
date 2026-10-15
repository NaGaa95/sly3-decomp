// The EE ABI passes the fifth integer argument in t0.
#include "m2c_prelude.h"
typedef struct Record { s32 first, second, third, fourth; } Record;
typedef struct State { u8 unknown[0x18C]; Record entries[8]; u32 count; } State;
void func_001A0548(State *state, s32 first, s32 second, s32 third, s32 fourth) {
    u32 count = state->count;
    if (count < 8) {
        Record *entry = &state->entries[count];
        state->count = count + 1;
        entry->first = first;
        entry->second = second;
        entry->third = third;
        entry->fourth = fourth;
    }
}

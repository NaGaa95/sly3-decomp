// Float and integer argument banks are independent in the original EE ABI.
#include "m2c_prelude.h"
typedef struct Record { s32 fourth; f32 scalar; s32 first, second, third, fifth; } Record;
typedef struct State { u8 unknown[0xB8]; s32 count; Record *entries; } State;
void func_00283278(State *state, s32 first, s32 second, s32 third, s32 fourth, s32 fifth, f32 scalar) {
    s32 count = state->count;
    if (count < 64) {
        Record *entry = &state->entries[count];
        state->count = count + 1;
        entry->first = first;
        entry->second = second;
        entry->third = third;
        entry->fourth = fourth;
        entry->scalar = scalar;
        entry->fifth = fifth;
    }
}

// The EE ABI passes the fifth through eighth integer arguments in t0 through t3.
#include "m2c_prelude.h"
typedef struct Record { s32 first, second, third, fourth, fifth, sixth, seventh; } Record;
typedef struct State { u8 unknown0[0x40]; s32 disabled; u8 unknown1[0x5C]; s32 count; Record *entries; } State;
void func_00188198(State *state, s32 first, s32 second, s32 third, s32 fourth, s32 fifth, s32 sixth, s32 seventh) {
    if (!state->disabled) {
        s32 count = state->count;
        if (count < 32) {
            Record *entry = &state->entries[count];
            state->count = count + 1;
            entry->first = first;
            entry->second = second;
            entry->third = third;
            entry->fourth = fourth;
            entry->fifth = fifth;
            entry->sixth = sixth;
            entry->seventh = seventh;
        }
    }
}

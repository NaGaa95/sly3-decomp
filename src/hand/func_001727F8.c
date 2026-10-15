// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct Record { s32 first, second, third; } Record;
typedef struct Group { u8 reserved[0xE4]; s32 count; Record *entries; u32 reservedEC; } Group;
typedef struct State { u8 reserved[0x5C]; s32 count; Group *groups; } State;
void func_001727F8(State *state, s32 first, s32 second, s32 third) {
    if (state->count != 0) {
        s32 offset = state->count * (s32)sizeof(Group) - (s32)sizeof(Group);
        Group *group = (Group *)((u32)state->groups + offset);
        if (group->count < 32) {
            Record *record = &group->entries[group->count++];
            record->first = first;
            record->second = second;
            record->third = third;
        }
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct Record {
    s32 first, second, third; u8 reserved[0x10]; s32 type;
    f32 value; u8 reserved24[8]; f32 duration;
} Record;
typedef struct State { u8 reserved[0x1F4]; u32 count; Record entries[4]; } State;
void func_0019F588(State *state, s32 first, s32 second, s32 third, f32 value) {
    if (state->count < 4U) {
        Record *record = &state->entries[state->count++];
        record->first = first;
        record->second = second;
        record->third = third;
        record->value = value;
        record->duration = -1.0f;
        record->type = 30;
    }
}

// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct Record { s32 first, key, third; f32 value, duration; } Record;
typedef struct State { u8 reserved[0x2E8]; u32 count; Record entries[12]; } State;
void func_00287A28(State *state, s32 first, s32 key, s32 third, f32 value, f32 duration) {
    if (state->count < 12U && key != -1) {
        Record *record = &state->entries[state->count++];
        record->first = first;
        record->key = key;
        record->third = third;
        record->value = value;
        record->duration = duration;
    }
}

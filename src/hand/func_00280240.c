// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct Record { s32 first, second; } Record;
typedef struct State { u8 reserved[0x138]; u32 count; Record entries[4]; } State;
void func_00280240(State *state, s32 first, s32 second) {
    if (state->count < 4U) {
        Record *record = &state->entries[state->count++];
        record->first = first;
        record->second = second;
    }
}

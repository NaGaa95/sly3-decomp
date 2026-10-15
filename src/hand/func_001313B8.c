// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct Record { s32 identifier; f32 x, y, z; } Record;
typedef struct State { u8 reserved[0xDC]; s32 count; Record *entries; } State;
void func_001313B8(State *state, s32 identifier, s32 x, s32 y, f32 z) {
    if (state->count < 8) {
        Record *record = &state->entries[state->count++];
        record->identifier = identifier;
        record->x = x;
        record->y = y;
        record->z = z;
    }
}

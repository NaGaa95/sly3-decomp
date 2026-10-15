// SLY3_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original bounded record insertion, with verified field sizes.
#include "m2c_prelude.h"

typedef struct Record { s32 identifier; f32 x, y, z, u, v; } Record;
typedef struct State { u8 reserved[0xD0]; s32 count; Record *entries; } State;
void func_00131358(State *state, s32 identifier, s32 x, s32 y, f32 z, f32 u, f32 v) {
    if (state->count < 8) {
        Record *record = &state->entries[state->count++];
        record->identifier = identifier;
        record->x = x;
        record->y = y;
        record->z = z;
        record->u = u;
        record->v = v;
    }
}

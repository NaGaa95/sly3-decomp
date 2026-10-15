// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Remove leading sample records, rebasing the retained sample offsets.
#include "m2c_prelude.h"
typedef struct Record { s32 offset, value; } Record;
typedef struct State { u16 *samples; u8 unknown0[0x80]; f32 period; u8 unknown1[8]; f32 duration; s32 count; Record entries[1]; } State;
void func_00264DE0(State *state, s32 removed) {
    Record *source = &state->entries[removed];
    Record *end = &state->entries[state->count];
    Record *dest = state->entries;
    s32 base = source->offset;
    state->samples += base;
    while (source < end) {
        *dest = *source;
        dest->offset -= base;
        source++;
        dest++;
    }
    state->count -= removed;
    state->duration = state->count * state->period;
}

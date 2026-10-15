// SLY3_ASFIX: engine-local-jumps
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Search the fixed-size records for a matching 128-bit mask.
#include "m2c_prelude.h"
typedef union Mask { u32 words[4]; u8 bytes[16]; } Mask;
typedef struct Record { s32 unknown[4]; Mask mask; } Record;
typedef struct State { u8 unknown0[0x4D0]; s32 count; u8 unknown1[0xC]; Record entries[1]; } State;
static inline s32 equal_mask(const Mask *left, const Mask *right) {
    s32 i;
    for (i = 0; i < 16; ++i) {
        if (left->bytes[i] != right->bytes[i]) return 0;
    }
    return 1;
}
Record *func_00255418(State *state, Mask mask) {
    s32 i;
    for (i = 0; i < state->count; ++i) {
        Record *record = &state->entries[i];
        if (equal_mask(&record->mask, &mask)) return record;
    }
    return NULL;
}

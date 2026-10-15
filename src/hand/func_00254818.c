// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Return the stored value when no bits selected by the global mask are present.
#include "m2c_prelude.h"
typedef union Mask { u32 words[4]; u8 bytes[16]; } Mask;
typedef struct State { u8 unknown0[0x2F4]; Mask mask; u8 unknown1[0xD00]; s32 value; } State;
extern Mask D_00475440, D_00475460;
static inline Mask intersect_mask(const Mask *left, const Mask *right) {
    Mask result;
    s32 i;
    for (i = 0; i < 16; ++i) result.bytes[i] = left->bytes[i] & right->bytes[i];
    return result;
}
static inline s32 unequal_mask(const Mask *left, const Mask *right) {
    s32 i;
    for (i = 0; i < 16; ++i) {
        if (left->bytes[i] != right->bytes[i]) return 1;
    }
    return 0;
}
s32 func_00254818(State *state) {
    Mask result = intersect_mask(&D_00475460, &state->mask);
    if (unequal_mask(&result, &D_00475440)) return 0;
    return state->value;
}

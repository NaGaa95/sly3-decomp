// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Parse decimal digits after an optional minus sign and return bytes consumed.
#include "m2c_prelude.h"

s32 func_0026FBD0(const u8 *text, s32 *result) {
    const u8 *cursor = text;
    s32 value = 0;
    s32 sign = *cursor == '-' ? -1 : 1;
    s32 consumed = 0;
    if (sign == -1) {
        cursor += 1;
        consumed = 1;
    }
    if ((u32)(*cursor - '0') < 10U) {
        do {
            s32 next = value * 10 - '0';
            u8 digit = *cursor;
            cursor += 1;
            consumed += 1;
            value = next + digit;
        } while ((u32)(*cursor - '0') < 10U);
    }
    *result = value * sign;
    return consumed;
}

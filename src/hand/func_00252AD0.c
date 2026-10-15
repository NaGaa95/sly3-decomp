// Initialize a 128-bit byte mask and optionally set one selected bit.
#include "m2c_prelude.h"
typedef union Mask { u32 words[4]; u8 bytes[16]; } Mask;
extern Mask D_00475440;
Mask *func_00252AD0(Mask *output, s32 bit) {
    Mask value = D_00475440;
    if (bit != -1) {
        value.bytes[bit / 8] |= 1 << (bit & 7);
    }
    *output = value;
    return output;
}

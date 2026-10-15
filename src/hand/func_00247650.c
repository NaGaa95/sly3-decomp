// Reset active resources, wait for the original SDK operation, and initialize the embedded lists.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011AF40(void *);                      /* extern */
M2C_UNK func_0011E210(void *);                      /* extern */
M2C_UNK func_00247588(void *);                            /* extern */
s32 func_002908F0(void);                                /* extern */
M2C_UNK func_002910B8(void);                            /* extern */
M2C_UNK func_00291CA8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00292034(void *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_002BF360(void *, M2C_UNK);             /* extern */

void func_00247650(void *arg0) {
    func_00247588(arg0);
    func_002910B8();
    func_00291CA8(0x524B5553, 0xA, 0, 0, 0, 0, 0);
    do {

    } while (func_002908F0() != 0);
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x1E4) = 0;
    M2C_FIELD(arg0, s32 *, 0xEC) = 0;
    M2C_FIELD(arg0, s32 *, 0xF0) = 0;
    M2C_FIELD(arg0, s32 *, 0xF4) = 0;
    M2C_FIELD(arg0, s32 *, 0xF8) = 0;
    M2C_FIELD(arg0, s32 *, 0xFC) = 0;
    M2C_FIELD(arg0, s32 *, 0x100) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = -1;
    func_00292034(arg0 + 0x10C, 0, 0xC);
    M2C_FIELD(arg0, s32 *, 0x214) = 0;
    func_00292034(arg0 + 0x218, 0, 0x20);
    func_002BF360(arg0 + 0x238, 0);
    func_0011E210(arg0 + 0x1C);
    func_0011E210(arg0 + 0x34);
    func_0011AF40(arg0 + 0x4C);
}

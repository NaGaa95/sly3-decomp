// Initialize the two state values, mark the tagged flags, and bind the requested record.
// Bit zero distinguishes an immediate flag word from a pointer to flag storage.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
M2C_UNK func_001F3BF8(void *);
/* extern */ M2C_UNK func_00238508(void *);
/* extern */ M2C_UNK func_0023B978(void *, s32);
/* extern */ s32 func_0023F3B8(void *, s32);
/* extern */ M2C_UNK func_0024DCF8(void *, s32);
/* extern */ M2C_UNK func_0028F068(void *, void *, M2C_UNK);
/* extern */ void func_0024D9D8(void *arg0) {
    s32 temp_2;
    s32 temp_3;
    s32 temp_5;
    func_001F3BF8(arg0);
    func_0028F068(arg0, M2C_FIELD(arg0, void **, 0x48), 1);
    func_0028F068(arg0, M2C_FIELD(arg0, void **, 0x4C), 1);
    temp_3 = M2C_FIELD(arg0, s32 *, 0x3C);
    if ((temp_3 ^ 1) & 1) {
        M2C_FIELD(temp_3, s32 *, 0) = (s32) (M2C_FIELD(temp_3, s32 *, 0) | 0x20);
    }
    else {
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) (temp_3 | 0x20);
    }
    temp_5 = M2C_FIELD(arg0, s32 *, 0x294);
    if (temp_5 != -1) {
        temp_2 = func_0023F3B8(arg0, temp_5);
        M2C_FIELD(arg0, s32 *, 0x298) = temp_2;
        if (temp_2 != 0) {
            func_0024DCF8(arg0, temp_2);
            func_0023B978(arg0, M2C_FIELD(arg0, s32 *, 0x298));
        }
    }
    func_00238508(arg0 + 0x29C);
}

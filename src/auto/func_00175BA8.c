// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_00175BA8(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, s32 *, 0x60) + (((s32) ((arg1 - M2C_FIELD(arg0, s32 *, 8)) * 0xCCCCCCCD) >> 3) * 0x60);
}

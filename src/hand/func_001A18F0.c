// Preserve the original object-pair predicate and state-dependent score limits.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-schedule-insns
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_0013B500(void *, s32);                 /* extern */
s32 func_0013CD00(s32, s32);                    /* extern */
s32 func_0023E178(void *object, void *peer);                                /* extern */

s32 func_001A18F0(void *object, void *peer) {
    s32 score;
    s32 result;

    score = func_0023E178(object, peer);
    if (func_0013B500(peer, 0x33) != 0) {
        if ((M2C_FIELD(peer, s32 *, 0x508) == 1) && (object == M2C_FIELD(peer, void **, 0x514))) {
            score = func_0013CD00(score, 1);
        }
        result = score;
        if ((u32) (M2C_FIELD(peer, s32 *, 0x33C) - 8) < 2U) {
            result = score;
            if (object == M2C_FIELD(peer, void **, 0x32C)) {
                score = func_0013CD00(score, 1);
                goto block_7;
            }
        }
    } else {
block_7:
        result = score;
    }
    return result;
}

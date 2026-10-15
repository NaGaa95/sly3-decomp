// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_0012C650(s32, s32, s32, s32);          /* extern */
M2C_UNK func_0013B540(void *);                      /* extern */

s32 func_0024AC98(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    func_0013B540(arg1);
    func_0012C650(arg0, M2C_FIELD(arg1, s32 *, 4), arg2, arg3);
    return arg0;
}

// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_0012C7D0(s32, s32, M2C_UNK); /* extern */
M2C_UNK func_0012C718(s32, s32, s32, s32); /* extern */
M2C_UNK func_0012C650(s32, s32, s32, s32);          /* extern */
M2C_UNK func_0013B540(void *);                      /* extern */

s32 func_0024AD00(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    func_0013B540(arg1);
    if (func_0012C7D0(M2C_FIELD(arg1, s32 *, 4), arg2, 0) != 0) {
        func_0012C718(arg0, M2C_FIELD(arg1, s32 *, 4), arg2, arg3);
    } else {
        func_0012C650(arg0, M2C_FIELD(arg1, s32 *, 4), arg2, arg3);
    }
    return arg0;
}

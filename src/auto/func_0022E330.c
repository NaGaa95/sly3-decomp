// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
f32 func_0022DE50(s32 curve, f32 parameter);                                /* extern */
M2C_UNK func_0022E148(s32, s32, s32, f32);          /* extern */

void func_0022E330(s32 arg0, s32 arg1, s32 arg2, f32 parameter) {
    func_0022E148(arg0, arg1, arg2, func_0022DE50(arg0, parameter));
}

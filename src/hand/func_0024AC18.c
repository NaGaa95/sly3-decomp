#include "sidebag_set_api.h"
// Resolve the descriptor through its original normal or extended-identifier path and return the output.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

s32 func_00249CF8(void *, s32);                     /* extern */
M2C_UNK func_0024A588(s32, void *, s32, s32);       /* extern */

s32 func_0024AC18(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    if (arg2 < 0x718) {
        func_0024A588(arg0, arg1, func_00249CF8(arg1, arg2), arg3);
    } else {
        func_0012C718((CRef *)arg0, (struct SidebagSetOwner *)M2C_FIELD(arg1, s32 *, 4), arg2, (const CRef *)arg3);
    }
    return arg0;
}

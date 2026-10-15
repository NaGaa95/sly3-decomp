// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_00235EC8();                                /* extern */
extern s32 D_00479D98;

s32 func_00235F40(void) {
    s32 var_v0;

    var_v0 = func_00235EC8();
    if (var_v0 == 0) {
        var_v0 = D_00479D98;
    }
    return var_v0;
}

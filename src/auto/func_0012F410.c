// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_0012F448();                                /* extern */
M2C_UNK func_0028EDC8(s32, s32, void *);            /* extern */

void func_0012F410(void *arg0) {
    if (func_0012F448() != 0) {
        func_0028EDC8(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), arg0);
    }
}

// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_00257EC8(void *arg0, s32 *arg1) {
    s32 *temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 **, 0x1764);
    if (temp_v0 != arg1) {
        if (temp_v0 != NULL) {
            *temp_v0 = 0;
        }
        M2C_FIELD(arg0, s32 **, 0x1764) = arg1;
        if (arg1 != NULL) {
            *arg1 = 1;
        }
    }
}

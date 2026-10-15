// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_0013B298(s32 *); /* extern */
M2C_UNK func_0013B100(s32 *); /* extern */

void func_0013B320(s32 *arg0) {
    s32 temp_v1;

    temp_v1 = *arg0;
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_0013B100(arg0);
        func_0013B298(arg0);
        return;
    case 1:
        func_0013B298(arg0);
        func_0013B100(arg0);
        return;
    }
}

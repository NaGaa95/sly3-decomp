// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
s32 func_0013B1C0(void *);        /* extern */
M2C_UNK func_0013B298(void *); /* extern */
M2C_UNK func_002A0480(M2C_UNK);                         /* extern */
M2C_UNK func_00296DB8(s32);                              /* extern */

void func_0013B078(void *arg0) {
    s32 temp_a0;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_a0 = M2C_FIELD(arg0, s32 *, 4);
        if (temp_a0 >= 0) {
            func_00296DB8(temp_a0);
        }
        M2C_FIELD(arg0, s32 *, 4) = -1;
        break;
    case 1:
        if (func_0013B1C0(arg0) != 0) {
            func_002A0480(0);
            func_0013B298(arg0);
        }
        M2C_FIELD(arg0, s32 *, 8) = 0;
        break;
    }
    M2C_FIELD(arg0, s32 *, 0) = -1;
}

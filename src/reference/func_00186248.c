// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_00186298(s32);                         /* extern */
M2C_UNK func_00186338(s32);                         /* extern */
s32 func_00187CB8();                                /* extern */
extern s32 D_004794C4;

void func_00186248(s32 arg0) {
    if (func_00187CB8() == 0) {
        if (D_004794C4 != 0) {
            func_00186298(D_004794C4);
        }
        func_00186338(arg0);
    }
}

// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_00131610(void *, M2C_UNK);             /* extern */
M2C_UNK func_00238980();                            /* extern */
M2C_UNK func_00252FC0(s32, s32);                    /* extern */

void func_00131770(void *arg0) {
    func_00238980();
    func_00131610(arg0, 1);
    func_00252FC0(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, s32 *, 0x3C));
}

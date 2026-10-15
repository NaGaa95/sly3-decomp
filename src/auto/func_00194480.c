// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_001746C0();                         /* extern */
M2C_UNK func_0027E660(s32, s32, s32, M2C_UNK); /* extern */
M2C_UNK func_0027E290(s32);                    /* extern */
M2C_UNK func_001748F8(s32);                      /* extern */

void func_00194480(s32 arg0, s32 arg1, s32 arg2) {
    func_001746C0();
    func_0027E290(arg0);
    func_0027E660(arg0, arg1, arg2, 0);
    func_0027E290(arg0);
    func_001748F8(arg0);
}

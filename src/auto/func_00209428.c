// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_001309D8(void *);                      /* extern */

void func_00209428(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xA0) != 0) {
        func_001309D8(arg0 + 0x94);
        func_001309D8(arg0 + 0x98);
        func_001309D8(arg0 + 0x9C);
        M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    }
}

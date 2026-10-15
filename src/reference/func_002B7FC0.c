// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_002B7F50();                            /* extern */
extern M2C_UNK D_00356060;

void *func_002B7FC0(void *arg0) {
    func_002B7F50();
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_00356060;
    return arg0;
}

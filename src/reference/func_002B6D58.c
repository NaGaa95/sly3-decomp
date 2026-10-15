// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
void *func_002B5328(void *receiver);                            /* extern */
extern M2C_UNK D_00351598;

void *func_002B6D58(void *arg0) {
    func_002B5328(arg0);
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_00351598;
    return arg0;
}

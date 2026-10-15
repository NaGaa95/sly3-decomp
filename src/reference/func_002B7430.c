// Original first base call consumes the unchanged receiver in A0.
// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
void *func_002B5898(void *receiver);                            /* extern */
extern M2C_UNK D_00362C28;

void *func_002B7430(void *arg0) {
    func_002B5898(arg0);
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_00362C28;
    return arg0;
}

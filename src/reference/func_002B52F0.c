// Original first base call consumes the unchanged receiver in A0.
// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
void *func_002B8670(void *receiver);                            /* extern */
extern M2C_UNK D_0035C398;

void *func_002B52F0(void *arg0) {
    func_002B8670(arg0);
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_0035C398;
    return arg0;
}

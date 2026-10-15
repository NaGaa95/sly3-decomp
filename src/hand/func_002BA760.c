// Sly 3 control flow reconstructed from the original function.
#include "m2c_prelude.h"

void func_002BA760(void **arg0, void *arg1) {
    if (arg1 != NULL) {
        M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + 1);
    }
    *arg0 = arg1;
}

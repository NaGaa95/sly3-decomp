// Original A1 is the nullable owner passed unchanged to the base initializer.
// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_00279998(void *);                         /* extern */
void func_001FC968(void *receiver, void *owner);                            /* extern */

void func_002797C0(char *arg0, void *owner) {
    func_001FC968(arg0, owner);
    func_00279998(arg0);
}

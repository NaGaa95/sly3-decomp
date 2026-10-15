// Original A1 is the nullable owner passed unchanged to the base initializer.
// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_0026E150(void *);                         /* extern */
void func_001FC968(void *receiver, void *owner);                            /* extern */

void func_0026E6C8(char *arg0, void *owner) {
    func_001FC968(arg0, owner);
    func_0026E150(arg0);
}

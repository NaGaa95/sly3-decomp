#include "m2c_prelude.h"
void *func_001FBFF0(void *, void *);

void func_001FC090(void *resource, void *object) {
    void *temp_v0;

    temp_v0 = func_001FBFF0(resource, object);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 8) = 0;
    }
}

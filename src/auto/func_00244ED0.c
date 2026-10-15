#include "m2c_prelude.h"
struct S;
void func_00245320(struct S *, unsigned short mask, unsigned short value);

void func_00244ED0(void *arg0, f32 fparg0) {
    if (fparg0 != M2C_FIELD(arg0, f32 *, 0x18)) {
        M2C_FIELD(arg0, f32 *, 0x18) = fparg0;
        func_00245320(arg0, 0x40, 0x40);
    }
}

// Initialize ownership and transform, acquire the resource, then attach the optional object.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "activation_selector_api.h"
#include "m2c_prelude.h"

M2C_UNK func_0013BD00(s32, void *);                 /* extern */
void *func_0017E1B8(M2C_UNK *, M2C_UNK, M2C_UNK, void *); /* extern */
M2C_UNK func_001F3BF8(void *);                            /* extern */
M2C_UNK func_0023ED58(void *, s128);                /* extern */
extern s128 D_00317560;
extern M2C_UNK D_00475480;

void func_002855B8(void *arg0) {
    void *temp_2;
    s32 temp_4;

    func_001F3BF8(arg0);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x204), void **, 0x164) = arg0;
    func_0023ED58(arg0, D_00317560);
    temp_2 = func_0017E1B8(&D_00475480, 4, 0x27D, arg0);
    M2C_FIELD(arg0, void **, 0x2D8) = temp_2;
    if (temp_2 != 0) {
        func_0023AAE8(temp_2, arg0, -1, 0, (void **)((char *)arg0 + 0x2DC));
    }
    temp_4 = M2C_FIELD(arg0, s32 *, 0x2E4);
    if (temp_4 != 0) {
        func_0013BD00(temp_4, arg0);
    }
}

// Remove list membership, record the clock, and release the attached component.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011B028(M2C_UNK *, void *);           /* extern */
M2C_UNK func_00203030(void *);                      /* extern */
M2C_UNK func_0023CE08(void *);                            /* extern */
M2C_UNK func_00256470(s32, void *);                 /* extern */
extern f32 D_0036BB98;
extern M2C_UNK D_00479B5C;

void func_002529F8(void *arg0) {
    s32 temp_4;
    void *temp_2;
    void *temp_3;
    void *temp_4_2;

    func_0023CE08(arg0);
    func_0011B028(&D_00479B5C, arg0);
    temp_4 = M2C_FIELD(arg0, s32 *, 0x3D8);
    if (temp_4 != 0) {
        func_00256470(temp_4, arg0);
    }
    temp_4_2 = M2C_FIELD(arg0, void **, 0x17C8);
    M2C_FIELD(arg0, f32 *, 0x1158) = (f32) D_0036BB98;
    if (temp_4_2 != NULL) {
        func_00203030(temp_4_2);
        temp_3 = M2C_FIELD(arg0, void **, 0x17C8);
        temp_2 = M2C_FIELD(temp_3, void **, 0xC);
        M2C_FIELD(temp_2, M2C_UNK (**)(void *), 0x14)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x10));
        M2C_FIELD(arg0, void **, 0x17C8) = NULL;
    }
}

// Configure the timed display resource, copy its parameters, and activate the resolved object.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00157688(void *, M2C_UNK);             /* extern */
M2C_UNK func_0022EA88(s32, s128, M2C_UNK *, void *, M2C_UNK, M2C_UNK, void *); /* extern */
M2C_UNK func_0022EEA0(s32, s128, M2C_UNK *, void *, M2C_UNK, M2C_UNK, void *, f32); /* extern */
void *func_00238690(void *, M2C_UNK);               /* extern */
M2C_UNK func_00238978(void);                            /* extern */
extern M2C_UNK D_00474FD0;

void func_00157538(void *arg0) {
    void *temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_2_4;
    void *temp_3;

    func_00238978();
    temp_3 = M2C_FIELD(arg0, void **, 0x10);
    if (M2C_FIELD(arg0, f32 *, 0x38) >= 0.0f) {
        temp_2 = M2C_FIELD(temp_3, void **, 0xC);
        func_0022EEA0(M2C_FIELD(arg0, s32 *, 0x30), M2C_FIELD(M2C_FIELD(temp_2, void *(**)(void *), 0x124)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x120)), s128 *, 0x30), &D_00474FD0, arg0 + 0x40, 0, 0, arg0 + 0x38, M2C_FIELD(arg0, f32 *, 0x38));
    } else {
        temp_2_2 = M2C_FIELD(temp_3, void **, 0xC);
        func_0022EA88(M2C_FIELD(arg0, s32 *, 0x30), M2C_FIELD(M2C_FIELD(temp_2_2, void *(**)(void *), 0x124)(temp_3 + M2C_FIELD(temp_2_2, s16 *, 0x120)), s128 *, 0x30), &D_00474FD0, arg0 + 0x40, 0, 0, arg0 + 0x38);
    }
    temp_2_3 = func_00238690(M2C_FIELD(arg0, void **, 0x10) + 0x29C, 0xF4);
    M2C_FIELD(temp_2_3, s32 *, 0x30) = (s32) M2C_FIELD(arg0, s32 *, 0x58);
    M2C_FIELD(temp_2_3, s32 *, 0x38) = (s32) M2C_FIELD(arg0, s32 *, 0x5C);
    M2C_FIELD(temp_2_3, f32 *, 0x3C) = (f32) M2C_FIELD(arg0, f32 *, 0x60);
    func_00157688(arg0, 1);
    temp_2_4 = M2C_FIELD(temp_2_3, void **, 0xC);
    M2C_FIELD(temp_2_4, M2C_UNK (**)(void *), 0x44)(temp_2_3 + M2C_FIELD(temp_2_4, s16 *, 0x40));
}

// Update the selected mode and timestamp, then configure and notify the matching component.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
#include "resource_attachment_api.h"

M2C_UNK func_00238AE8(void *);                      /* extern */
extern f32 D_0036BB98;

void func_001DA630(void *arg0, s32 arg1) {
    void *temp_2;
    void *temp_2_2;
    void *temp_3;
    void *temp_3_2;

    if (arg1 != M2C_FIELD(arg0, s32 *, 0x30)) {
        func_00238AE8(arg0 + 0x18);
        M2C_FIELD(arg0, s32 *, 0x30) = arg1;
        M2C_FIELD(arg0, f32 *, 0x34) = (f32) D_0036BB98;
        switch (arg1) {                             /* irregular */
        case 1:
            temp_2 = func_00238690(M2C_FIELD(arg0, void **, 0x10) + 0x29C, 0xC9);
            M2C_FIELD(temp_2, s32 *, 0x3C) = 2;
            temp_3 = M2C_FIELD(temp_2, void **, 0xC);
            M2C_FIELD(temp_3, M2C_UNK (**)(void *), 0x44)(temp_2 + M2C_FIELD(temp_3, s16 *, 0x40));
            return;
        case 0:
            temp_2_2 = func_00238690(M2C_FIELD(arg0, void **, 0x10) + 0x29C, 0xC9);
            M2C_FIELD(temp_2_2, s32 *, 0x3C) = 0xE;
            temp_3_2 = M2C_FIELD(temp_2_2, void **, 0xC);
            M2C_FIELD(temp_3_2, M2C_UNK (**)(void *), 0x44)(temp_2_2 + M2C_FIELD(temp_3_2, s16 *, 0x40));
            break;
        }
    }
}

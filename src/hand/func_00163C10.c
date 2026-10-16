// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"
#include "resource_attachment_api.h"

#include "wait_bind_api.h"
M2C_UNK func_001982C8(s32, s32);
M2C_UNK func_00238AB8(void *);
M2C_UNK func_00238AE8(void *);
extern f32 D_0036BB98;

void func_00163C10(void *arg0, s32 arg1) {
    s32 temp_2;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_2_4;
    void *temp_3;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x30);
    if (arg1 != temp_2) {
        if (temp_2 == 0) {
            func_001982C8(M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 0x10) + 0x1168);
        }
        func_00238AE8(arg0 + 0x18);
        M2C_FIELD(arg0, s32 *, 0x30) = arg1;
        M2C_FIELD(arg0, f32 *, 0x34) = (f32) D_0036BB98;
        switch (arg1) {                             /* irregular */
        case 0:
            temp_2_2 = func_00238690(M2C_FIELD(arg0, void **, 0x10) + 0x29C, 0xD3);
            func_00197838((struct WaitBindState *)temp_2_2, (struct WaitBindTemplate *)M2C_FIELD(arg0, s32 *, 0x38), 0, (struct WaitBindOverride *)(M2C_FIELD(arg0, s32 *, 0x10) + 0x1168));
            temp_2_3 = M2C_FIELD(temp_2_2, void **, 0xC);
            M2C_FIELD(temp_2_3, M2C_UNK (**)(void *), 0x44)(temp_2_2 + M2C_FIELD(temp_2_3, s16 *, 0x40));
            break;
        case 1:
            temp_2_4 = func_00238690(M2C_FIELD(arg0, void **, 0x10) + 0x29C, 0xCA);
            temp_3 = M2C_FIELD(temp_2_4, void **, 0xC);
            M2C_FIELD(temp_2_4, s32 *, 0x38) = (s32) M2C_FIELD(arg0, s32 *, 0x3C);
            M2C_FIELD(temp_3, M2C_UNK (**)(void *), 0x44)(temp_2_4 + M2C_FIELD(temp_3, s16 *, 0x40));
            break;
        case -1:
            func_00238AB8(arg0);
            break;
        }
    }
}

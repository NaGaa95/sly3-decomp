// Leave or enter the active state, update the registration and notify the attached receiver.
// Registration context is supplied by callers but not consumed by its original helper.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-schedule-insns
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

void func_001F4B00(void *context, s32 selection, void *object);      /* extern */
extern f32 D_0036BB98;
extern char D_00475480[];

void func_001E8E60(void *object, s32 state) {
    s32 previous_state;
    s32 selection;
    void *temp_2_2;
    void *temp_2_3;
    void *temp_3;
    void *temp_3_2;

    previous_state = M2C_FIELD(object, s32 *, 0x194);
    if (previous_state != state) {
        if (previous_state == 0) {
            selection = M2C_FIELD(object, s32 *, 0x130);
            if (selection != -1) {
                func_001F4B00(D_00475480, selection, M2C_FIELD(object, void **, 0x190));
            }
            temp_3 = M2C_FIELD(object, void **, 0x1BC);
            if (temp_3 != NULL) {
                temp_2_2 = M2C_FIELD(temp_3, void **, 0xC);
                M2C_FIELD(temp_2_2, void (**)(void *), 0x1B4)(temp_3 + M2C_FIELD(temp_2_2, s16 *, 0x1B0));
            }
        }
        M2C_FIELD(object, s32 *, 0x194) = state;
        M2C_FIELD(object, f32 *, 0x198) = (f32) D_0036BB98;
        if (state == 0) {
            func_001F4B00(D_00475480, M2C_FIELD(M2C_FIELD(object, void **, 0x190), s32 *, 0x130), object);
            temp_3_2 = M2C_FIELD(object, void **, 0x1BC);
            M2C_FIELD(object, s32 *, 0x1B4) = 0;
            M2C_FIELD(object, s32 *, 0x19C) = 0;
            M2C_FIELD(object, s32 *, 0x1A0) = 0;
            M2C_FIELD(object, s32 *, 0x1C0) = 0;
            if (temp_3_2 != NULL) {
                temp_2_3 = M2C_FIELD(temp_3_2, void **, 0xC);
                M2C_FIELD(temp_2_3, void (**)(void *), 0x1C4)(temp_3_2 + M2C_FIELD(temp_2_3, s16 *, 0x1C0));
            }
        }
    }
}

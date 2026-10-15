// Initialize all eleven shared resource pools on their first constructor registration.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0011E100(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern s32 D_0036AE78;
extern s32 D_0036AE7C;
extern s32 D_0036AE80;
extern s32 D_0036AE84;
extern s32 D_0036AE88;
extern s32 D_0036AE8C;
extern s32 D_0036AE98;
extern s32 D_0036AE9C;
extern s32 D_0036AEA0;
extern s32 D_0036AEA4;
extern s32 D_0036AEA8;
extern M2C_UNK D_004D2AD8;
extern M2C_UNK D_004D2BB0;
extern M2C_UNK D_004D2C88;
extern M2C_UNK D_004D2D60;
extern M2C_UNK D_004D2E38;
extern M2C_UNK D_004D2F10;
extern M2C_UNK D_004D2F28;
extern M2C_UNK D_004D2F40;
extern M2C_UNK D_004D2F58;
extern M2C_UNK D_004D2F70;
extern M2C_UNK D_004D2F88;

void func_0012BED0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_10;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 temp_2_4;
    s32 temp_2_5;
    s32 temp_2_6;
    s32 temp_2_7;
    s32 temp_2_8;
    s32 temp_2_9;
    s32 temp_3;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        temp_3 = D_0036AE78 + 1;
        D_0036AE78 = temp_3;
        if (temp_3 == 1) {
            func_0011E100(&D_004D2AD8, 0x10, 0x800, 0x10);
        }
        temp_2 = D_0036AE7C + 1;
        D_0036AE7C = temp_2;
        if (temp_2 == 1) {
            func_0011E100(&D_004D2BB0, 0x18, 0x400, 0x10);
        }
        temp_2_2 = D_0036AE80 + 1;
        D_0036AE80 = temp_2_2;
        if (temp_2_2 == 1) {
            func_0011E100(&D_004D2C88, 0x18, 0x100, 0x10);
        }
        temp_2_3 = D_0036AE84 + 1;
        D_0036AE84 = temp_2_3;
        if (temp_2_3 == 1) {
            func_0011E100(&D_004D2D60, 0x1C, 0x400, 0x10);
        }
        temp_2_4 = D_0036AE88 + 1;
        D_0036AE88 = temp_2_4;
        if (temp_2_4 == 1) {
            func_0011E100(&D_004D2E38, 0xC, 0x100, 0x10);
        }
        temp_2_5 = D_0036AE8C + 1;
        D_0036AE8C = temp_2_5;
        if (temp_2_5 == 1) {
            func_0011E100(&D_004D2F10, 0x18, 0x100, 0x10);
        }
        temp_2_6 = D_0036AE98 + 1;
        D_0036AE98 = temp_2_6;
        if (temp_2_6 == 1) {
            func_0011E100(&D_004D2F28, 0x20, 0x100, 0x10);
        }
        temp_2_7 = D_0036AE9C + 1;
        D_0036AE9C = temp_2_7;
        if (temp_2_7 == 1) {
            func_0011E100(&D_004D2F40, 0x50, 0x100, 0x10);
        }
        temp_2_8 = D_0036AEA0 + 1;
        D_0036AEA0 = temp_2_8;
        if (temp_2_8 == 1) {
            func_0011E100(&D_004D2F58, 0x20, 0x40, 0x10);
        }
        temp_2_9 = D_0036AEA4 + 1;
        D_0036AEA4 = temp_2_9;
        if (temp_2_9 == 1) {
            func_0011E100(&D_004D2F70, 0xC, 0x40, 0x10);
        }
        temp_2_10 = D_0036AEA8 + 1;
        D_0036AEA8 = temp_2_10;
        if (temp_2_10 == 1) {
            func_0011E100(&D_004D2F88, 0x10, 0x20, 0x10);
        }
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"
M2C_UNK func_001CEF70(void *);
#include "save_state_api.h"
M2C_UNK func_001D0630(void *, void *);
 M2C_UNK func_0021D290(s32);
 void func_0021D360(void *);
 extern s32 D_004793C8;
void func_001CF640(void *arg0, s32 arg1) {
    s32 temp_4;
    s32 temp_5;
    s32 var_17;
    if (M2C_FIELD(arg0, s32 *, 8) == 5) {
        var_17 = 0;
        if (D_004793C8 != 0) {
            func_001CEF70(arg0 + 0x13960);
            do {
                temp_5 = var_17 * 0x6864;
                var_17 += 1;
                func_001D0630(arg0, arg0 + (temp_5 + 0x24));
            }
            while (var_17 < 3);
            M2C_FIELD(arg0, s32 *, 0xC) = 6;
            func_001CF430(arg0, 6);
            if (arg1 & 0x20) {
                temp_4 = M2C_FIELD(arg0, s32 *, 0x13954);
                if (temp_4 != 0) {
                    func_0021D290(temp_4);
                    func_0021D360((void *)M2C_FIELD(arg0, s32 *, 0x13954));
                }
            }
        }
    }
}

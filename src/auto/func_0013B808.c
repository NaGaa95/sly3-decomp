// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
void func_0012BC20(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0027A10C;
extern M2C_UNK D_0027A1D8;
extern M2C_UNK D_002BAAE8;
extern f32 D_002DDED0;
extern M2C_UNK D_003DD490;
extern f32 *D_003E0E80;
extern M2C_UNK D_003E1144;
extern M2C_UNK D_004520A8;

void func_0013B808(s32 arg0, s32 arg1) {
    struct {
        M2C_UNK m0;
        char pad0[0xC];
        M2C_UNK m10;
    } fr;
    func_0012B218((s32) (void *)&fr, 0);
    func_0024AD00((s32) &fr.m10, arg0, arg1, (s32) (void *)&fr);
    func_0012BC20(&fr.m10);
    func_0012BC20((void *)&fr);
}

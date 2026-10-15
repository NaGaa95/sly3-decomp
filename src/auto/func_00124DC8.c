// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
void func_0012AF00(s32, M2C_UNK *);              /* extern */
void func_0012BC20(M2C_UNK *);                   /* extern */
M2C_UNK func_0012A0B0(M2C_UNK *, M2C_UNK);          /* extern */
extern f32 D_002DDED0;
extern M2C_UNK D_002DDF40;
extern M2C_UNK D_003DD040;
extern M2C_UNK D_003DD490;
extern s32 D_003E0F9C;
extern s32 D_003E0FA0;
extern s32 D_003E0FA4;
extern M2C_UNK D_004520A8;

s32 func_00124DC8(s32 arg0, s32 arg1, s32 arg2) {
    struct {
        M2C_UNK m0;
    } fr;
    func_0012B008((s32) (void *)&fr, M2C_FIELD(arg2, s32 *, 4));
    func_0012AF00(arg0, (void *)&fr);
    func_0012BC20((void *)&fr);
    return arg0;
}

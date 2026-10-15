// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
extern s128 D_002A2DD0;
extern M2C_UNK D_002BBB60;
extern M2C_UNK D_002D9BE0;
extern M2C_UNK D_002D9C70;
extern M2C_UNK D_002D9D00;
extern s32 D_002DD5BC;
extern M2C_UNK D_002DDFA0;
extern s32 D_002E1E40;
extern s32 D_002F7900;
extern M2C_UNK D_003DD040;
extern M2C_UNK D_003DD08C;
extern M2C_UNK D_003DD490;

void func_00244ED0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    if (fparg0 != M2C_FIELD(arg0, f32 *, 0x18)) {
        M2C_FIELD(arg0, f32 *, 0x18) = fparg0;
        func_00245320(arg0, 0x40, 0x40);
    }
}

// Reset and notify the associated object resources in their original sequence.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_0016D840(void *, M2C_UNK);             /* extern */
M2C_UNK func_00170360(s32);                         /* extern */
M2C_UNK func_001703C8(s32, s32, M2C_UNK);           /* extern */
M2C_UNK func_001854C8(M2C_UNK *, M2C_UNK, void *);  /* extern */
M2C_UNK func_00238978(void);                            /* extern */
M2C_UNK func_002389C0(void *);                      /* extern */
M2C_UNK func_0023DF78(void *);                      /* extern */
M2C_UNK func_00256828(void *, M2C_UNK, M2C_UNK, s128); /* extern */
M2C_UNK func_00256DF0(void *);                      /* extern */
extern s128 D_00317560;
extern M2C_UNK D_0036C700;

void func_0016D670(void *arg0) {
    s32 temp_5;

    func_00238978();
    func_0016D840(arg0, 0);
    func_001854C8(&D_0036C700, 0x18, M2C_FIELD(arg0, void **, 0x10));
    func_00256DF0(M2C_FIELD(arg0, void **, 0x10));
    func_00256828(M2C_FIELD(arg0, void **, 0x10), 0, 0, D_00317560);
    func_0023DF78(M2C_FIELD(arg0, void **, 0x10));
    func_002389C0(arg0);
    func_00170360(M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x10D0));
    temp_5 = M2C_FIELD(arg0, s32 *, 0x3C);
    if (temp_5 != 0) {
        func_001703C8(M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x10D0), temp_5, 2);
    }
}

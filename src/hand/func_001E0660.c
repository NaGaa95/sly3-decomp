// Release the stored handles and configure the associated object before recording its owner and time.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"
M2C_UNK func_001309D8(s32);
/* extern */ M2C_UNK func_0013CD10(M2C_UNK *, void *);
/* extern */
#include "owner_parent_link.h"
M2C_UNK func_0023FC90(void *, M2C_UNK);
/* extern */ M2C_UNK func_0028F068(void *, void *, s32);
/* extern */ extern f32 D_0036BB98;
extern M2C_UNK D_00475480;
void func_001E0660(void *arg0) {
    void *temp_16;
    void *temp_2;
    void *temp_3;
    func_001309D8(arg0 + 0x1544);
    func_001309D8(arg0 + 0x1548);
    func_001309D8(arg0 + 0x154C);
    func_001309D8(arg0 + 0x1550);
    func_001309D8(arg0 + 0x1740);
    func_001309D8(arg0 + 0x1744);
    func_001309D8(arg0 + 0x1750);
    func_001309D8(arg0 + 0x1754);
    func_001309D8(arg0 + 0x1758);
    func_001309D8(arg0 + 0x175C);
    temp_3 = M2C_FIELD(arg0, void **, 0x1540);
    if (temp_3 != NULL) {
        temp_2 = M2C_FIELD(temp_3, void **, 0xC);
        M2C_FIELD(temp_2, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK), 0x1C)(temp_3 + M2C_FIELD(temp_2, s16 *, 0x18), 6, 0, 0, 0, 0);
        temp_16 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x1540), void **, 0x190);
        func_0028F068(temp_16, M2C_FIELD(temp_16, void **, 0x48), M2C_FIELD(arg0, s32 *, 0x1554));
        func_0028F068(temp_16, M2C_FIELD(temp_16, void **, 0x4C), M2C_FIELD(arg0, s32 *, 0x1558));
        func_0023FC90(temp_16, 0);
        func_001C7A00(temp_16, 0, 0xF);
        M2C_FIELD(arg0, void **, 0x156C) = temp_16;
        M2C_FIELD(arg0, f32 *, 0x1570) = (f32) D_0036BB98;
        func_0013CD10(&D_00475480, arg0);
    }
}

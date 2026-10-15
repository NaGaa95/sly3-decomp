// Execute the eligible transition or the ordered global update and fallback routines.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_001854C8(M2C_UNK *, M2C_UNK, void *);  /* extern */
s32 func_00186900(void *);                          /* extern */
M2C_UNK func_00187270(void *);                      /* extern */
M2C_UNK func_001874E8(void *);                      /* extern */
M2C_UNK func_001878E0(void *, M2C_UNK);             /* extern */
M2C_UNK func_00283F70(M2C_UNK *);                   /* extern */
M2C_UNK func_002846A8(M2C_UNK *);                   /* extern */
M2C_UNK func_00284778(M2C_UNK *);                   /* extern */
s32 func_002852B0(M2C_UNK *);                       /* extern */
extern M2C_UNK D_0036C700;
extern M2C_UNK D_004BC230;

void func_001871C0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xB8) == 0) {
        func_001854C8(&D_0036C700, 0x24, arg0);
        if (func_00186900(arg0) != 0) {
            func_001878E0(arg0, 1);
            return;
        }
        if (func_002852B0(&D_004BC230) != 0) {
            func_002846A8(&D_004BC230);
            func_00284778(&D_004BC230);
            func_00283F70(&D_004BC230);
            return;
        }
        func_00187270(arg0);
        func_001874E8(arg0);
    }
}

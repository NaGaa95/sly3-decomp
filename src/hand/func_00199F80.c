// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "m2c_prelude.h"

s32 func_0013B500(void *, M2C_UNK);
M2C_UNK func_0013BEC0(void);
#include "path_task_api.h"


void func_00199F80(void *arg0, s32 arg1, void *arg2) {
    func_0013BEC0();
    if ((arg1 == 1) || (arg1 == 3)) {
        if (func_0013B500(arg2, 0x3A) != 0) {
            func_00199118(arg0, func_001990D0(arg0, arg2), 2, 0);
        }
    }
}

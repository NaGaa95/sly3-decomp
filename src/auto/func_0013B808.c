#include "m2c_prelude.h"

void func_0012BC20(M2C_UNK *);

void func_0013B808(void *arg0, s32 arg1) {
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

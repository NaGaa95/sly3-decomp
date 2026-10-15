// Run the original component updates and conditionally emit the final object notification.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Original EE call/control flow reconstructed with physical-register arguments.
#include "m2c_prelude.h"

M2C_UNK func_00204048(void *);                      /* extern */
M2C_UNK func_002045B0(void *);                      /* extern */
M2C_UNK func_00204E00(void *);                      /* extern */
M2C_UNK func_00205238(void *);                      /* extern */
M2C_UNK func_00205750(void *);                      /* extern */
s32 func_002058D8(void *);                          /* extern */
M2C_UNK func_00207928(void *);                      /* extern */
M2C_UNK func_0023C660(void *);                            /* extern */
M2C_UNK func_0023E228(void *);                      /* extern */

void func_00203FB0(void *arg0) {
    func_0023C660(arg0);
    func_00204048(arg0);
    func_00205750(arg0);
    func_00205238(arg0);
    func_00207928(arg0);
    func_00204E00(arg0);
    func_002045B0(arg0);
    if ((M2C_FIELD(arg0, f32 *, 0x33C) != 0.0f) || ((M2C_FIELD(arg0, s32 *, 0x428) != 0) && (func_002058D8(arg0) != 0))) {
        func_0023E228(arg0);
    }
}

#include "heap_frame_api.h"
// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "m2c_prelude.h"
M2C_UNK func_001A30A8();
/* extern */ extern M2C_UNK D_0035B528;
void func_001A2D30(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, M2C_UNK **, 0x30) = &D_0035B528;
    func_001A30A8();
    if (arg1 & 1) {
        func_001D2818(arg0);
    }
}

#include "m2c_prelude.h"
#include "transition_counter_api.h"
s32 func_001852E0(M2C_UNK *);
M2C_UNK func_00185328(M2C_UNK *, s32);
extern M2C_UNK D_0036C700;

void func_001F7C70(void *unused_receiver, int unused_mode) {
    func_00185328(&D_0036C700, func_001852E0(&D_0036C700) + 1);
}

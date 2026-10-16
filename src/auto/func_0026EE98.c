#include "m2c_prelude.h"
#include "actor_task_clone_api.h"

void func_0026EE98(struct ACTOR_TASK *arg0, const struct ACTOR_TASK *arg1, void *arg2, void *arg3) {
    s32 temp_v0;
    func_0012F378(arg0, arg1, arg2, arg3);
    temp_v0 = M2C_FIELD(arg3, s32 *, 0xA8);
    M2C_FIELD(arg0, s32 *, 0x1C) = temp_v0;
}

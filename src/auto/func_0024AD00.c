#include "sidebag_insert_api.h"
#include "sidebag_set_api.h"
#include "m2c_prelude.h"
s32 func_0012C7D0(s32, s32, M2C_UNK); /* extern */
M2C_UNK func_0013B540(void *);                      /* extern */

s32 func_0024AD00(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    func_0013B540(arg1);
    if (func_0012C7D0(M2C_FIELD(arg1, s32 *, 4), arg2, 0) != 0) {
        func_0012C718((CRef *)arg0, (struct SidebagSetOwner *)M2C_FIELD(arg1, s32 *, 4), arg2, (const CRef *)arg3);
    } else {
        func_0012C650((CRef *)arg0, (struct SidebagSetOwner *)M2C_FIELD(arg1, s32 *, 4), arg2, (const CRef *)arg3);
    }
    return arg0;
}

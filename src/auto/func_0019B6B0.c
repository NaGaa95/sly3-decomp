#include "m2c_prelude.h"
#include "contact_notify_supplied_side_api.h"
void func_0023E110(void *receiver,void *event);

void func_0019B6B0(void *arg0, void *arg1,int unused_side) {
    func_0023E110(arg0,arg1);
    M2C_FIELD(arg1, f32 *, 0x94) = 0.0f;
    M2C_FIELD(arg1, f32 *, 0x98) = 0.0f;
}

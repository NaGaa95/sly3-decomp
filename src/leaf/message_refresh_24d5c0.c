// SLY3_CFLAGS: -Os -G0
#include "actor_state_resource_api.h"
struct RefreshOwner { char prefix[0xF90]; void *object; };
extern char D_00475480[];
void func_0013BEC0(void);
int func_0013B500(void *,int);
void func_0024BF20(void *);
void func_0024C118(void *);
void func_0024D5C0(void *receiver,int message,void *payload)
{
    struct RefreshOwner *owner;
    func_0013BEC0();
    if(message!=0x18) return;
    owner=func_001F4AD0(D_00475480,0);
    if(owner && func_0013B500(owner,0x33) && owner->object) {
        func_0024BF20(owner->object);
        func_0024C118(owner->object);
    }
}

// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
struct EngineStateReceiver { unsigned char prefix[0x194]; int state; };
extern unsigned char D_00475480[];
extern struct DEFERRED_PMF D_00321F40;
void func_0015DD68(void *game,unsigned int mask,void *receiver,struct DEFERRED_PMF member,void *owner);
void func_0019BB00(struct EngineStateReceiver *receiver,int state,void *owner)
{
    if(receiver->state==state) return;
    receiver->state=state;
    if(state) func_0015DC68(D_00475480,receiver,D_00321F40,owner);
    else func_0015DD68(D_00475480,3,receiver,D_00321F40,0);
}

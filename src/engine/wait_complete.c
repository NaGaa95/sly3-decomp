// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
typedef struct WaitCompleteState {
    char unaccessed[0x10];
    void *owner;
    char unaccessed14[0x4C-0x14];
    int identifier;
    int value;
    int mode;
} WaitCompleteState;
CRef *func_0024AEF8(CRef *output,int count,int type,void *values);
void func_002534C0(void *owner,CRef *reference,int value,int mode);
void func_00198490(WaitCompleteState *state)
{
    int absent=-1;
    if(state->identifier!=absent) {
        CRef reference;
        func_0024AEF8(&reference,1,0x100F,&state->identifier);
        func_002534C0(state->owner,&reference,state->value,state->mode);
        state->value=state->identifier=absent;
        state->mode=0;
        func_0012BC20(&reference);
    }
}

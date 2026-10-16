// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
#include "wait_bind_api.h"
typedef struct WaitBindDescriptor WaitBindDescriptor;
typedef struct WaitBindTemplate {
    void *reference;
    char unaccessed[0x40-4];
    WaitBindDescriptor *descriptor;
} WaitBindTemplate;
typedef struct WaitBindOverride {
    WaitBindDescriptor *descriptor;
    unsigned int word4;
} WaitBindOverride;
typedef struct WaitBindMethod {
    short adjustment, reserved;
    void (*notify)(void *,int,int,int,void *const *,CRef *);
} WaitBindMethod;
typedef struct WaitBindState {
    void *reference;
    unsigned char record4[8];
    WaitBindMethod *table;
    char unaccessed10[0x30-0x10];
    WaitBindTemplate *current;
    unsigned int word34;
    WaitBindDescriptor *descriptor;
    float started;
    int active;
    WaitBindOverride *override;
    unsigned int word48;
} WaitBindState;
void func_00238AE8(void *slot);
void func_002BAA50(void *slot,void *reference);
void func_002BBF40(void *slot,void *reference);
void func_00197A10(void *state,WaitBindDescriptor *descriptor);
void func_00198490(void *state);
static inline void Notify(WaitBindState *state,int event)
{
    WaitBindMethod *method=&state->table[3];
    method->notify((char *)state+method->adjustment,event,0,0,0,0);
}
void func_00197838(WaitBindState *state,WaitBindTemplate *value,
                   unsigned int word,WaitBindOverride *override)
{
    if(value==state->current)
        return;
    if(state->current) {
        func_00238AE8((char *)state+0x18);
        Notify(state,3);
        func_002BAA50(state,0);
        func_002BBF40(state->record4,0);
        state->word34=0;
        func_00197A10(state,0);
        state->active=0;
        state->word48=0;
        func_00198490(state);
    }
    state->current=value;
    if(!value)
        return;
    func_002BAA50(state,value->reference);
    Notify(state,2);
    state->word48=word;
    {
        WaitBindDescriptor *selected;
        if(!override||!(selected=override->descriptor)) {
            WaitBindTemplate *current=state->current;
            selected=current->descriptor;
            state->word34=(unsigned int)current;
        } else {
            state->override=override;
            state->word34=override->word4;
        }
        func_00197A10(state,selected);
    }
    state->override=0;
}

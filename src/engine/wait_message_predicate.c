// SLY3_CFLAGS: -Os -G0
struct WaitMessageState {
    char unaccessed[0x48];
    unsigned int word48;
};
#include "empty_message_api.h"
int func_00198500(struct WaitMessageState *state,int event,void *unused_message)
{
    switch(event) {
    case 18:
    case 19:
        if(state->word48)
            return 1;
        break;
    }
    return func_00238AD8(state,event,unused_message);
}

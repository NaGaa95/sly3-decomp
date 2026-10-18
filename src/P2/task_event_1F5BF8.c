// SLY3_CFLAGS: -Os -G0
#include "empty_message_api.h"
struct EventOwner { unsigned char prefix[0x11CC]; int mode; };
struct EventReceiver { unsigned char prefix[0x10]; struct EventOwner *owner; };
void func_001F6148(void *receiver, int state, void *context);
int func_001F5BF8(struct EventReceiver *receiver, int event, void *context)
{
    switch (event) {
    case 15:
        if (receiver->owner->mode != 1)
            break;
        func_001F6148(receiver, 6, context);
        return 1;
    case 8:
        func_001F6148(receiver, 4, context);
        return 1;
    }
    return func_00238AD8(receiver, event, context);
}

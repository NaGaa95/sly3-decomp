// SLY3_CFLAGS: -Os -G0
#include "empty_message_api.h"
struct GateOwner {
    unsigned char prefix[0x10F4];
    void *tracked;
};
struct GateReceiver {
    unsigned char prefix[0x10];
    struct GateOwner *owner;
};
void func_00256DF0(void *);
int func_001DA860(struct GateReceiver *receiver, int event, void *message)
{
    if (event == 1) {
        if (receiver->owner->tracked == message) {
            func_00256DF0(receiver->owner);
            return 1;
        }
    }
    return func_00238AD8(receiver, event, message);
}

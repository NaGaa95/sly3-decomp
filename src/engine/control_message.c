// SLY3_CFLAGS: -Os -G0
#include "empty_message_api.h"
struct ControlEmitter;
struct ControlMessage { int word0, word4, kind; };
struct ControlMessageState { unsigned char unaccessed00[0x30]; int mode; };
void func_00134AE0(struct ControlEmitter *);
int func_00134950(struct ControlMessageState *receiver, int event, struct ControlMessage *message)
{
    if (event == 10 && message->kind == 0x2AA && receiver->mode == 3)
        func_00134AE0((struct ControlEmitter *)receiver);
    return func_00238AD8(receiver, event, message);
}

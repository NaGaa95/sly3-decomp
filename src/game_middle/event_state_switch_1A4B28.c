// SLY3_CFLAGS: -Os -G0
#include "empty_message_api.h"
void func_001A4800(void *receiver, int state, void *message);
int func_00238AA8(void *receiver);
int func_001A4B28(void *receiver, int event, void *message)
{
    switch (event) {
    case 0xE:
    case 0xF:
    case 0x11: {
        int state;
        switch (event) {
        case 0xF:
            state = 6;
            break;
        case 0xE:
            state = 7;
            break;
        case 0x11:
            state = 8;
            break;
        }
        func_001A4800(receiver, state, message);
        return 1;
    }
    case 0x13:
        if (!func_00238AA8(receiver))
            func_001A4800(receiver, 9, message);
        return 1;
    }
    return func_00238AD8(receiver, event, message);
}

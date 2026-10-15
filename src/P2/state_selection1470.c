// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "actor_input_query.h"

struct StateReceiver {
    char prefix[0x298];
    int fallback;
    char tail[0x1470 - 0x29C];
    int state;
};

int func_001B5C78(void *context, int *mode);
void *func_001C4088(void *context, int *mode);
int func_001BD718(void *context, int *mode);
void func_0024DF48(void *receiver, int result, int mode);

int func_001F0E38(struct StateReceiver *receiver)
{
    int result = func_001530F8(receiver);
    if (result != -1)
        return result;
    switch (receiver->state) {
    case 1:
    case 4:
        return 1;
    }
    return -1;
}

void func_001F0E98(struct StateReceiver *receiver)
{
    int mode = 0;
    int result;
    switch (receiver->state) {
    case 6:
        result = func_001B5C78((char *)receiver + 0x500, &mode);
        break;
    case 7:
        result = (int)func_001C4088((char *)receiver + 0xE40, &mode);
        break;
    case 5:
        result = func_001BD718((char *)receiver + 0x320, &mode);
        break;
    default:
        result = 0;
        break;
    }
    if (!result)
        result = receiver->fallback;
    func_0024DF48(receiver, result, mode);
}

int func_001F0F48(const struct StateReceiver *receiver)
{
    switch (receiver->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return 1;
    }
    return 0;
}

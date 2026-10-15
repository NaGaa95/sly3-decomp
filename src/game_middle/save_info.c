// SLY3_CFLAGS: -Os -G0
#include "card_commands.h"
struct SaveInfoContext {
    int port, slot;
    unsigned char opaque08[4];
    int state;
    unsigned char opaque10[4];
    float nextQueryTime;
    int cardType, freeBlocks, formatted;
    unsigned char opaque24[0x13960 - 0x24];
    unsigned char commandContext[1];
};
extern float D_0036BBD8;
int func_002A2B68(int port, int slot, int *type, int *freeBlocks, int *formatted);

int func_001D0658(void *save)
{
    struct SaveInfoContext *context = save;
    void *commandContext = context->commandContext;
    int request;
    int result;
    request = func_002A2B68(context->port, context->slot,
        &context->cardType, &context->freeBlocks, &context->formatted);
    result = func_001CEFC8(commandContext, request, 1, 0);
    switch (result) {
    case 9:
    case 11:
        context->state = 1;
        break;
    case 10:
    case 12:
        result = 12;
        context->state = 2;
        break;
    case 0:
        if (context->formatted) {
            if (context->state < 3)
                context->state = 3;
        } else {
            context->state = 2;
        }
        break;
    }
    if (result == 0 || result == 12) {
        if (context->cardType != 2) {
            result = 11;
            context->state = 1;
        }
    }
    context->nextQueryTime = D_0036BBD8 + 0.3f;
    return result;
}

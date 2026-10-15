// SLY3_CFLAGS: -Os -G0
#include "card_commands.h"

struct CardCommandSave {
    int port;
    int slot;
    unsigned char opaque08[0x13960 - 8];
    unsigned char commandContext[1];
};

int func_002A27B8(int descriptor, void *buffer, int bytes);
int func_002A2F10(int port, int slot, const char *path);

int func_001D0918(void *save, int descriptor, void *buffer, int bytes, int *readBytes)
{
    struct CardCommandSave *context = save;
    void *commandContext = context->commandContext;
    return func_001CEFC8(commandContext,
        func_002A27B8(descriptor, buffer, bytes), 5, readBytes);
}

int func_001D0B08(void *save, const char *path)
{
    struct CardCommandSave *context = save;
    void *commandContext = context->commandContext;
    int result = func_001CEFC8(commandContext,
        func_002A2F10(context->port, context->slot, path), 15, 0);
    return result == 14 ? 0 : result;
}

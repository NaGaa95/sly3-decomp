// Sly 3 USA memory-card open and write command wrappers.
// SLY3_CFLAGS: -Os -G0
#include "card_transfer_api.h"
#include "card_commands.h"

struct CardTransferSaveView {
    int port;
    int slot;
    unsigned char opaque08[0x13960 - 8];
    unsigned char commandContext[1];
};
int func_002A24E8(int port, int slot, const char *path, int mode);
int func_002A28D0(int descriptor, void *buffer, int bytes);

int func_001D0860(void *save, const char *path, int mode, int *descriptor)
{
    struct CardTransferSaveView *context = save;
    void *commandContext = context->commandContext;
    return func_001CEFC8(commandContext,
        func_002A24E8(context->port, context->slot, path, mode),
        2, descriptor);
}

int func_001D0970(void *save, int descriptor, void *buffer, int bytes, int *written)
{
    struct CardTransferSaveView *context = save;
    void *commandContext = context->commandContext;
    return func_001CEFC8(commandContext,
        func_002A28D0(descriptor, buffer, bytes), 6, written);
}

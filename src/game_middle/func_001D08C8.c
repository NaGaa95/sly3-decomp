// Close an open memory-card file and wait for the command to finish.
// SLY3_CFLAGS: -Os -G0
#include "card_commands.h"
struct CardSave {
    unsigned char opaque00[0x13960];
    unsigned char commandContext[1];
};
int func_002A2648(int fd);
int func_001D08C8(void *savePointer, int fd)
{
    struct CardSave *save = savePointer;
    return func_001CEFC8(save->commandContext, func_002A2648(fd), 3, 0);
}

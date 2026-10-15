// Sly 3 USA save directory and three-block bootstrap.
// SLY3_CFLAGS: -Os -G0
#include "save_bootstrap_api.h"
#include "card_commands.h"

struct CardSaveBlock {
    unsigned char bytes[0x6864];
};
struct CardSave {
    int port;
    int slot;
    unsigned char opaque08[0x24 - 8];
    struct CardSaveBlock blocks[3];
    unsigned char opaque13950[0x10];
    unsigned char commandContext[1];
};
typedef char card_save_block_stride[(sizeof(struct CardSaveBlock) == 0x6864) ? 1 : -1];
extern char D_00323A00[], D_00323A18[], D_00323A48[];

int func_001D09C8(void *save, void *path, void *data, int bytes);
int func_001D00A0(void *save, char *directory, char *title);
int func_001D02D0(void *save, char *directory);
int func_001D0508(void *save, struct CardSaveBlock *block);
int func_002A2610(int port, int slot, const char *path);

int func_001CF7B8(void *savePointer)
{
    struct CardSave *save = savePointer;
    int result;
    int i;

    result = func_001D0808(save, D_00323A00);
    if (result) return result;
    result = func_001D09C8(save, D_00323A18, D_00323A48, 5);
    if (result) return result;
    result = func_001D00A0(save, D_00323A00, D_00323A48);
    if (result) return result;
    result = func_001D02D0(save, D_00323A00);
    if (result) return result;
    for (i = 0; i < 3; i++) {
        result = func_001D0508(save, &save->blocks[i]);
        if (result) return result;
    }
    return 0;
}

int func_001D0808(void *savePointer, const char *path)
{
    struct CardSave *save = savePointer;
    void *commandContext = save->commandContext;
    int result = func_001CEFC8(commandContext,
        func_002A2610(save->port, save->slot, path), 0xB, 0);
    return result == 0x18 ? 0 : result;
}

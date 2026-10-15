// SLY3_CFLAGS: -Os -G0
#include "card_commands.h"
#include "card_directory_records.h"

struct ProbeSaveBlock {
    unsigned char bytes[0x6864];
};
struct ProbeSave {
    int port, slot, word8, state;
    unsigned char opaque10[0x24 - 0x10];
    struct ProbeSaveBlock blocks[3];
};
extern char D_00323A00[];
int func_002A2CE8(int port, int slot, char *path, int mode,
                  int limit, struct CardDirectoryRecord *records);
int func_001D0760(void *save, int *free_bytes);
int func_001D0588(void *save, void *block);

int func_001CFA40(void *storage)
{
    struct ProbeSave *save = storage;
    void *command_context = (char *)storage + 0x13960;
    int count, free_bytes, status, index;

    status = func_001CEFC8(command_context,
        func_002A2CE8(save->port, save->slot, D_00323A00, 0, -1, 0),
        0xD, &count);
    if (count <= 0) {
        func_001D0760(save, &free_bytes);
        if (free_bytes <= 0x1CBFF)
            save->state = 4;
        return 0xE;
    }
    index = 0;
    if (status)
        goto done;
    while (index < 3) {
        func_001D0588(save, &save->blocks[index++]);
        if (status)
            goto done;
    }
    if (save->state < 5)
        save->state = 5;
done:
    return status;
}

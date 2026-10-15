// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "card_directory_records.h"
struct SaveCardPort {
    int port, slot;
};
extern struct CardDirectoryRecord D_00374D00[];
extern char D_00375180[];
int func_002715F8(unsigned char *text);
int func_00271628(int destination_address, int source_address);
void *func_00292034(void *destination, int value, unsigned int bytes);
int func_002A2CE8(int port, int slot, char *path, int mode,
                  int limit, struct CardDirectoryRecord *records);
int func_001CEFC8(void *unused_context, int request, int command, int *result);
void func_001CE8F0(const struct CardDirectoryRecord *input,
                  struct CardConvertedRecord *output);

int func_001CFEF8(void *save, char *path, int limit,
                  struct CardConvertedRecord *output, int *completed)
{
    struct SaveCardPort *card = (struct SaveCardPort *)save;
    int mode, status, index;
    if (limit > 18)
        return 0x25;
    if (path) {
        if ((unsigned int)func_002715F8((unsigned char *)path) > 64)
            return 0xD;
        func_00271628((int)D_00375180, (int)path);
        mode = 0;
    } else {
        mode = 1;
        path = D_00375180;
    }
    func_00292034(D_00374D00, 0, 0x480);
    status = func_001CEFC8((char *)save + 0x13960,
                           func_002A2CE8(card->port, card->slot, path,
                                         mode, limit, D_00374D00),
                           0xD, completed);
    if (status)
        return status;
    for (index = 0; index < *completed; ++index)
        func_001CE8F0(&D_00374D00[index], &output[index]);
    return 0;
}

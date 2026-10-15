// SLY3_CFLAGS: -Os -G0
#include "card_directory_records.h"

struct SaveWriteCallbackView {
    unsigned char opaque00[0x13950];
    void *selectedBlock;
};
extern char D_003751D0[], D_00375240[];
int func_001D0658(void *save);
int func_001D0410(void *save, void *block);
void func_001D0D30(void *menu, int selection);
void func_001D0C08(void *menu, int mode);
void func_001D2100(void *menu);

int func_001CFC10(void *save)
{
    struct SaveWriteCallbackView *context = save;
    int result = func_001D0658(save);
    if (!result)
        result = func_001D0410(save, context->selectedBlock);
    if (result) {
        func_001D0D30(D_003751D0, 3);
        func_001D0C08(D_003751D0, 0x30);
        func_001D2100(D_00375240);
    }
    return result;
}

int func_001CFEF8(void *save, char *path, int limit,
    struct CardConvertedRecord *output, int *completed);

int func_001D0058(void *save, char *path, void *record)
{
    int count;
    int result = func_001CFEF8(save, path, 1, record, &count);
    if (result)
        return result;
    return count == 1 ? 0 : 14;
}

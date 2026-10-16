// SLY3_CFLAGS: -Os -G0
#include "attachment_selection_api.h"
struct AttachmentSelectionGame {
    char prefix[0x47A8];
    void *first;
    void *second;
};
void func_00173E48(void *space, AttachmentPackedPosition position, int attachmentWord, void **output);
void func_00173EE8(struct AttachmentSelectionGame *game, int selector,
                  AttachmentPackedPosition position, int attachmentWord, void **output)
{
    void *space;
    switch (selector) {
    case 0: space=game->first; break;
    case 1: space=game->second; break;
    default: space=0; break;
    }
    func_00173E48(space, position, attachmentWord, output);
}

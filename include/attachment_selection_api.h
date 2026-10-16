#ifndef SLY3_ATTACHMENT_SELECTION_API_H
#define SLY3_ATTACHMENT_SELECTION_API_H
#include "attachment_creation_api.h"
struct AttachmentSelectionGame;
#ifdef __cplusplus
extern "C" {
#endif
void func_00173EE8(struct AttachmentSelectionGame *game, int selector,
                  AttachmentPackedPosition position, int attachmentWord,
                  void **output);
#ifdef __cplusplus
}
#endif
#endif

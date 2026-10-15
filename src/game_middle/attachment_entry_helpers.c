// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "attachment_creation_api.h"
void *func_001738C0(void *space,AttachmentPackedPosition position,int attachmentWord) {
    void *result;
    func_00173778(space,position,attachmentWord,&result);
    return result;
}
struct AttachmentReferencePrefix {
    char pad0[0x10];
    int references;
};
void func_001738E0(void *receiver) {
    ++((struct AttachmentReferencePrefix *)receiver)->references;
}

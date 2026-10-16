// SLY3_CFLAGS: -Os -G0
#include "attachment_selection_api.h"
struct AttachmentResetOwner {
    char prefix[0x37C];
    void *attachment;
    char unused380[0x1024-0x380];
    unsigned int currentWord, savedWord;
};
struct AttachmentResetState {
    char prefix[0x10];
    struct AttachmentResetOwner *owner;
};
extern struct AttachmentSelectionGame D_00475480;
extern AttachmentPackedPosition D_00317560;
void func_00131770(void *receiver);
void func_0016D480(void *receiver, int mode);
void func_0016D418(struct AttachmentResetState *state)
{
    func_00131770(state);
    func_0016D480(state, -1);
    func_00173EE8(&D_00475480, -1, D_00317560, 0, &state->owner->attachment);
    state->owner->savedWord=state->owner->currentWord;
}

// SLY3_CFLAGS: -Os -G0
#include "attachment_selection_api.h"

struct ActivationMatrix { AttachmentPackedPosition row[4]; };
struct ActivationEntry {
    short adjustment, reserved;
    struct ActivationMatrix *(*method)(void *);
};
struct ActivationOwnerPrefix {
    unsigned char opaque00[0xC];
    struct ActivationEntry *table;
    unsigned char opaque10[0x37C - 0x10];
    void *attachment;
    unsigned char opaque380[0x10D0 - 0x380];
    void *requests;
};
struct ActivationStatePrefix {
    unsigned char opaque00[0x10];
    struct ActivationOwnerPrefix *owner;
};
extern struct AttachmentSelectionGame D_00475480;
extern unsigned char D_0036C700[];
void func_00131598(void *receiver);
void func_0016D480(void *receiver, int mode);
void func_00170360(void *requests);
void func_001854C8(void *context, int event, void *owner);

void func_0016D388(void *receiver)
{
    struct ActivationStatePrefix *state = receiver;
    struct AttachmentSelectionGame *game;
    struct ActivationEntry *entry;
    struct ActivationMatrix *matrix;
    func_00131598(state);
    func_0016D480(state, 0);
    func_00170360(state->owner->requests);
    func_001854C8(D_0036C700, 0xF, state->owner);
    game = &D_00475480;
    entry = state->owner->table + 36;
    matrix = entry->method((char *)state->owner + entry->adjustment);
    func_00173EE8(game, 1, matrix->row[3], (int)state->owner,
                  &state->owner->attachment);
}

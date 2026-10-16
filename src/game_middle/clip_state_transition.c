// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
#include "owned_record_list_api.h"

struct ClipStateMask { unsigned int words[4]; };
struct ClipStateEntry { short delta, reserved; void *function; };
struct ClipStateSubject {
    unsigned char opaque00[0xC];
    struct ClipStateEntry *table;
};
struct ClipStateMatrix { EE_ATTACHMENT_QWORD rows[4]; };
struct ClipStateOwner {
    unsigned char opaque00[0x2F4];
    struct ClipStateMask mask;
    unsigned char opaque304[0x10A8 - 0x304];
    int active;
};
struct ClipStateClip { int kind; };
struct ClipStateReceiver {
    unsigned char opaque00[0x10];
    struct ClipStateOwner *owner;
    unsigned char opaque14[4];
    unsigned char retained18[0x18];
    struct ClipStateSubject *subject;
    struct ClipStateClip *clip;
    int state;
    float changed;
};
struct ClipStateCommand {
    unsigned char opaque00[0xC];
    struct ClipStateEntry *table;
    unsigned char opaque10[0x38 - 0x10];
    struct ClipStateSubject *subject;
    unsigned int word3C;
    struct ClipStateClip *clip;
};
struct ClipStatePositionCommand {
    struct ClipStateCommand common;
    unsigned char opaque44[0xCC - 0x44];
    int mode;
    unsigned char opaqueD0[0x120 - 0xD0];
    int use_position;
};
struct ClipStateClock { float now, step; };
extern struct ClipStateClock D_0036BB98;
void *func_00255130(void *owner, const struct ClipStateMask *mask);
void func_00132930(void *command, EE_ATTACHMENT_QWORD position);
void func_00238AB8(void *receiver);

void func_001A3860(void *receiver, int state)
{
    struct ClipStateReceiver *source = receiver;
    if (state == source->state) return;
    func_00238AE8(source->retained18);
    source->state = state;
    source->changed = D_0036BB98.now;
    switch (state) {
    case 0:
        source->owner->active = 1;
        if (!source->clip) {
            struct ClipStateMask mask = source->owner->mask;
            source->clip = func_00255130(source->owner, &mask);
        }
        if (source->clip->kind == 2) {
            struct ClipStatePositionCommand *command =
                func_00238690((char *)source->owner + 0x29C, 0xCB);
            struct ClipStateSubject *subject;
            struct ClipStateEntry *entry;
            struct ClipStateMatrix *matrix;
            command->use_position = 1;
            command->mode = 2;
            command->common.clip = source->clip;
            command->common.subject = source->subject;
            subject = source->subject;
            entry = &subject->table[36];
            matrix = ((void *(*)(void *))entry->function)((char *)subject + entry->delta);
            func_00132930(command, matrix->rows[3]);
            entry = &command->common.table[8];
            ((void (*)(void *))entry->function)((char *)command + entry->delta);
        } else {
            struct ClipStateCommand *command =
                func_00238690((char *)source->owner + 0x29C, 0xC9);
            struct ClipStateEntry *entry;
            command->clip = source->clip;
            command->subject = source->subject;
            entry = &command->table[8];
            ((void (*)(void *))entry->function)((char *)command + entry->delta);
        }
        break;
    case -1:
        func_00238AB8(source);
        source->owner->active = 0;
        break;
    }
}

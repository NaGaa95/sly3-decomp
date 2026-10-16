// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
#include "owned_record_list_api.h"

struct SubjectWaitEntry { short delta, reserved; void *function; };
struct SubjectWaitCommand {
    unsigned char opaque00[0xC];
    struct SubjectWaitEntry *table;
    unsigned char opaque10[0x38 - 0x10];
    unsigned int word38;
    int mode;
};
struct SubjectWaitOwner {
    unsigned char opaque00[0x10CC];
    int active;
};
struct SubjectWaitReceiver {
    unsigned char opaque00[0x10];
    struct SubjectWaitOwner *owner;
    unsigned char opaque14[4];
    unsigned char retained18[0x18];
    int state;
    float changed;
    unsigned int word38;
};
struct SubjectWaitClock { float now, step; };
extern struct SubjectWaitClock D_0036BB98;
void func_00238AB8(void *receiver);

void func_001A5810(void *receiver, int state)
{
    struct SubjectWaitReceiver *source = receiver;
    if (state == source->state) return;
    func_00238AE8(source->retained18);
    if (!source->state) source->owner->active = 0;
    source->state = state;
    source->changed = D_0036BB98.now;
    switch (state) {
    case 0: {
        struct SubjectWaitCommand *command =
            func_00238690((char *)source->owner + 0x29C, 0xC9);
        struct SubjectWaitEntry *entry;
        command->mode = 0x24;
        command->word38 = source->word38;
        entry = &command->table[8];
        ((void (*)(void *))entry->function)((char *)command + entry->delta);
        source->owner->active = 1;
        break;
    }
    case -1:
        func_00238AB8(source);
        break;
    }
}

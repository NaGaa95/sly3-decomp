// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
#include "owned_record_list_api.h"

struct WaitCommandEntry { short delta, reserved; void *function; };
struct WaitCommand {
    unsigned char opaque00[0xC];
    struct WaitCommandEntry *table;
    unsigned char opaque10[0x30 - 0x10];
    int word30;
    unsigned char opaque34[8];
    int mode, enabled;
};
struct WaitCommandReceiver {
    unsigned char opaque00[0x10];
    char *owner;
    unsigned char opaque14[4];
    unsigned char retained18[0x18];
    int state;
    float changed;
    unsigned char opaque38[8];
    int selection;
};
struct WaitCommandClock { float now, step; };
extern struct WaitCommandClock D_0036BB98;

void func_001A5038(void *receiver, int state)
{
    struct WaitCommandReceiver *source = receiver;
    if (state == source->state) return;
    func_00238AE8(source->retained18);
    source->state = state;
    source->changed = D_0036BB98.now;
    switch (state) {
    case 0: {
        struct WaitCommand *command = func_00238690(source->owner + 0x29C, 0xCA);
        struct WaitCommandEntry *entry = &command->table[8];
        ((void (*)(void *))entry->function)((char *)command + entry->delta);
        break;
    }
    case 1: {
        struct WaitCommand *command = func_00238690(source->owner + 0x29C, 0xD2);
        struct WaitCommandEntry *entry;
        command->word30 = source->selection;
        command->enabled = 1;
        entry = &command->table[8];
        ((void (*)(void *))entry->function)((char *)command + entry->delta);
        break;
    }
    case 2: {
        struct WaitCommand *command = func_00238690(source->owner + 0x29C, 0xCA);
        struct WaitCommandEntry *entry;
        command->mode = 1;
        entry = &command->table[8];
        ((void (*)(void *))entry->function)((char *)command + entry->delta);
        break;
    }
    }
}

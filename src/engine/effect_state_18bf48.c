// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
#include "owned_record_list_api.h"

struct Clock { float time, step; };
extern struct Clock D_0036BB98;
struct VirtualEntry {
    short adjustment, reserved;
    void (*method)(void *);
};
struct Command {
    char prefix[0xC];
    struct VirtualEntry *table;
    char opaque10[0x28];
    int word38;
    int word3C;
};
struct Effect {
    char prefix[0x10];
    void *owner10;
    int word14;
    char retained18[0x18];
    int word30;
    char opaque34[8];
    int mode3C;
    float changed40;
};
void func_0018BF48(struct Effect *effect, int mode)
{
    if (mode == effect->mode3C) return;
    func_00238AE8(effect->retained18);
    effect->mode3C = mode;
    effect->changed40 = D_0036BB98.time;
    switch (mode) {
    case 0: {
        struct Command *command = func_00238690((char *)effect->owner10 + 0x29C, 0xC9);
        struct VirtualEntry *entry;
        command->word38 = effect->word30;
        command->word3C = 0x11;
        entry = command->table + 8;
        entry->method((char *)command + entry->adjustment);
        break;
    }
    case 1: {
        struct Command *command = func_00238690((char *)effect->owner10 + 0x29C, 0xCA);
        struct VirtualEntry *entry;
        command->word38 = effect->word30;
        entry = command->table + 8;
        entry->method((char *)command + entry->adjustment);
        break;
    }
    }
}

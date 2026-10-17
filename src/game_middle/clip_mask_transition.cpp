// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "resource_attachment_api.h"
extern "C" {
#include "owned_record_list_api.h"
}

struct ClipTransitionMask {
    unsigned char bytes[16];
    ClipTransitionMask() {}
    ClipTransitionMask(int index) asm("func_00252AD0");
    ClipTransitionMask operator|(const ClipTransitionMask &other) const {
        ClipTransitionMask result;
        for (int i = 0; i < 16; ++i)
            result.bytes[i] = bytes[i] | other.bytes[i];
        return result;
    }
};
struct ClipTransitionEntry { short delta, reserved; void *function; };
struct ClipTransitionCommand {
    unsigned char opaque00[0xC];
    ClipTransitionEntry *table;
    unsigned char opaque10[0x3C - 0x10];
    int mode;
    void *clip;
};
struct ClipTransitionOwner {
    unsigned char opaque00[0x10D0];
    void *controller;
};
struct ClipTransitionSubject {
    unsigned char opaque00[0x15F8];
    int enabled;
};
struct ClipTransitionReceiver {
    unsigned char opaque00[0x10];
    ClipTransitionOwner *owner;
    unsigned char opaque14[4];
    unsigned char retained18[0x18];
    ClipTransitionSubject *subject;
    int state;
    float changed;
};
struct ClipTransitionClock { float now, step; };
extern "C" {
extern ClipTransitionClock D_0036BB98;
void func_00238A38(void *receiver);
void func_002389C0(void *receiver);
void func_00238AB8(void *receiver);
int func_0013B500(void *object, int kind);
void *func_00255130(void *owner, const ClipTransitionMask *mask);
void func_001703C8(void *controller, void *subject, int mode);
void func_002541F8(void *owner, void *selected);
}

extern "C" void func_001A59C8(void *receiver, int state)
{
    ClipTransitionReceiver *source = (ClipTransitionReceiver *)receiver;
    if (state == source->state) return;
    if (!source->state) func_00238A38(source);
    func_00238AE8(source->retained18);
    source->state = state;
    source->changed = D_0036BB98.now;
    switch (state) {
    case 0: {
        ClipTransitionCommand *command = (ClipTransitionCommand *)
            func_00238690((char *)source->owner + 0x29C, 0xC9);
        if (source->subject && func_0013B500(source->subject, 0x37) &&
            source->subject->enabled) {
            ClipTransitionMask mask = ClipTransitionMask(0x41) | ClipTransitionMask(0x13);
            command->clip = func_00255130(source->owner, &mask);
        }
        command->mode = 0x13;
        ClipTransitionEntry *entry = &command->table[8];
        ((void (*)(void *))entry->function)((char *)command + entry->delta);
        func_001703C8(source->owner->controller, source->subject, 0);
        func_002541F8(source->owner, 0);
        func_002389C0(source);
        break;
    }
    case -1:
        func_00238AB8(source);
        break;
    }
}

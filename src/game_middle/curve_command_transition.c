// SLY3_CFLAGS: -Os -G0
#include "resource_attachment_api.h"
#include "owned_record_list_api.h"

typedef unsigned int CurveTransitionPosition __attribute__((mode(TI)));
struct CurveTransitionEntry { short delta, reserved; void *method; };
struct CurveTransitionOwner {
    unsigned char opaque00[0xC];
    struct CurveTransitionEntry *table;
};
struct CurveTransitionMatrix {
    CurveTransitionPosition basis[3];
    CurveTransitionPosition position;
};
struct CurveTransitionCommand {
    unsigned char opaque00[0xC];
    struct CurveTransitionEntry *table;
    unsigned char opaque10[0x28];
    unsigned int target;
    int mode;
};
struct CurveTransitionReceiver {
    unsigned char opaque00[0x10];
    struct CurveTransitionOwner *owner;
    unsigned char opaque14[4];
    unsigned char retained[0x18];
    unsigned char opaque30[0xC];
    int state;
    unsigned char opaque40[0x70];
    int mode;
    unsigned char opaqueB4[4];
    unsigned int target;
    unsigned char opaqueBC[4];
    CurveTransitionPosition position;
    float duration;
};
void func_001D8AA0(void *receiver, int state);

void func_001D8ED0(void *receiver, int state)
{
    struct CurveTransitionReceiver *source = receiver;
    if (state == source->state) return;
    func_00238AE8(source->retained);
    func_001D8AA0(source, state);
    switch (source->state) {
    case 0: {
        struct CurveTransitionCommand *command =
            func_00238690((char *)source->owner + 0x29C, 0xC9);
        struct CurveTransitionEntry *entry;
        struct CurveTransitionOwner *owner;
        struct CurveTransitionMatrix *matrix;
        command->mode = source->mode;
        if (source->mode == 13) command->target = source->target;
        entry = &command->table[8];
        ((void (*)(void *))entry->method)((char *)command + entry->delta);
        owner = source->owner;
        entry = &owner->table[36];
        matrix = ((struct CurveTransitionMatrix *(*)(void *))entry->method)
            ((char *)owner + entry->delta);
        source->position = matrix->position;
        source->duration = 1.5f;
        break;
    }
    case 1: {
        struct CurveTransitionCommand *command =
            func_00238690((char *)source->owner + 0x29C, 0xCA);
        struct CurveTransitionEntry *entry;
        command->target = source->target;
        entry = &command->table[8];
        ((void (*)(void *))entry->method)((char *)command + entry->delta);
        break;
    }
    }
}

// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct VEntry { short delta, pad; void *function; };
struct MatrixSet { float f[16]; } __attribute__((aligned(16)));
struct Source {
    unsigned char prefix00[0xC];
    struct VEntry *vtable;
    unsigned char gap10[0xF8 - 0x10];
    struct Source *next;
};
struct Owner {
    unsigned char prefix00[0xD8];
    int mode;
    unsigned int flags;
    unsigned char gapE0[0xF4 - 0xE0];
    struct Source **first;
};
struct Receiver {
    unsigned char prefix00[0x24];
    struct Receiver *next;
    unsigned char gap28[0x40 - 0x28];
    struct VEntry *vtable;
};
struct Frame {
    unsigned char prefix00[0x10];
    struct Owner *owner;
    unsigned char gap14[0x60 - 0x14];
    struct Source *attached;
    unsigned char gap64[0x6C - 0x64];
    struct Receiver *receivers;
};
void *func_00292034(void *destination, int value, unsigned int bytes);
void func_002BE948(void *object, int flags);
void func_00202E58(struct Frame *self)
{
    qword unused_temporary;
    struct MatrixSet matrices[32];
    int count = 0;
    if (self->owner->mode == 2) {
        struct Source *source;
        for (source = *self->owner->first; source && count < 32; source = source->next) {
            struct VEntry *entry = &source->vtable[36];
            matrices[count++] = *((struct MatrixSet *(*)(void *))entry->function)((char *)source + entry->delta);
        }
        if (count == 0)
            return;
    } else {
        count = 1;
        if (self->attached) {
            struct Source *source = self->attached;
            struct VEntry *entry = &source->vtable[36];
            unsigned int flags;
            matrices[0] = *((struct MatrixSet *(*)(void *))entry->function)((char *)source + entry->delta);
            flags = self->owner->flags;
            if (flags) {
                if (flags & 1) {
                    func_00292034(&matrices[0], 0, 0x30);
                    matrices[0].f[0] = matrices[0].f[5] = matrices[0].f[10] = 1.0f;
                }
                if (flags & 2)
                    matrices[0].f[12] = 0.0f;
                if (flags & 4)
                    matrices[0].f[13] = 0.0f;
                if (flags & 8)
                    matrices[0].f[14] = 0.0f;
            }
        } else {
            func_00292034(&matrices[0], 0, 0x40);
            matrices[0].f[0] = matrices[0].f[5] = matrices[0].f[10] = matrices[0].f[15] = 1.0f;
        }
    }
    {
        struct Receiver *receiver;
        for (receiver = self->receivers; receiver; receiver = receiver->next) {
            struct VEntry *entry = &receiver->vtable[4];
            ((void (*)(void *, int, struct MatrixSet *))entry->function)((char *)receiver + entry->delta, count, matrices);
        }
    }
    func_002BE948(&unused_temporary, 2);
}

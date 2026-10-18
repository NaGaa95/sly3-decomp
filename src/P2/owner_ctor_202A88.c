// SLY3_CFLAGS: -Os -G0
#include "common.h"
struct VEntry { short delta, pad; void *function; };
struct Child { unsigned char prefix[0x18]; struct VEntry *vtable; };
struct OwnerBase {
    unsigned char prefix00[0xC];
    struct VEntry *vtable;
    unsigned char gap10[0xD0 - 0x10];
    int childCount;
    struct Child **children;
    int mode;
    unsigned char gapDC[4];
    int valueE0;
    int valueE4;
};
struct Quad4 { qword rows[4]; };
struct Instance {
    unsigned char prefix00[0xC];
    void *vtable;
    struct OwnerBase *owner;
    int enabled;
    unsigned char gap18[8];
    struct Quad4 matrix;
    int value60;
    unsigned char gap64[4];
    float scale;
    unsigned char list[12];
};
extern char D_00361538[];
extern char D_00475480[];
struct Instance *func_002B8670(struct Instance *self);
void func_0011AF38(void *list, int linkOffset);
void func_0011AF60(void *list, void *item);
void func_00202C20(struct Instance *self);
void *func_00292034(void *destination, int value, unsigned int bytes);
struct Instance *func_00202A88(struct Instance *self, struct OwnerBase *owner, unsigned int flags)
{
    func_002B8670(self);
    self->vtable = D_00361538;
    self->owner = owner;
    self->scale = 1.0f;
    func_0011AF38(self->list, 0x24);
    func_00202C20(self);
    func_0011AF60(D_00475480 + 0x480C, self);
    if (self->owner->mode == 3)
        self->enabled = *(int *)(D_00475480 + 0x3EBC);
    else
        self->enabled = self->owner->valueE0;
    if (self->enabled) {
        float *m = (float *)&self->matrix;
        func_00292034(m, 0, 0x40);
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    } else {
        struct VEntry *entry = &owner->vtable[36];
        struct Quad4 *source = ((struct Quad4 *(*)(void *))entry->function)((char *)owner + entry->delta);
        self->matrix = *source;
    }
    if (self->owner->mode == 3)
        self->value60 = 0;
    else
        self->value60 = self->owner->valueE4;
    if (flags & 1) {
        int i;
        for (i = 0; i < self->owner->childCount; i++) {
            struct Child *child = self->owner->children[i];
            struct VEntry *entry = &child->vtable[3];
            ((void (*)(void *, struct Instance *))entry->function)((char *)child + entry->delta, self);
        }
    }
    return self;
}

// SLY3_CFLAGS: -Os -G0
struct FlushEntry { short delta, unused; void *method; };
struct FlushObject {
    unsigned char prefix0[0xC];
    struct FlushEntry *vtable;
    unsigned char gap10[0xDC - 0x10];
    struct FlushOwner *owner;
};
struct FlushLink { void *occupant; };
struct FlushNode {
    void *resource;
    struct FlushNode *next;
    struct FlushLink *link;
    struct FlushObject *object;
};
struct FlushOwner { unsigned char prefix[0x64]; struct FlushNode *head; };
struct FlushSelf {
    unsigned char prefix0[0xC];
    struct FlushEntry *vtable;
    unsigned char gap10[0xDC - 0x10];
    struct FlushOwner *owner;
    unsigned char gapE0[0x120 - 0xE0];
    unsigned long flags;
};
extern unsigned char D_00475480[];
void func_0023E068(void *self);
int func_001E5FF8(void *self);
int func_001E4F40(void *filter, void *object);
void func_001E5070(void *self, void *other, int mode);
int func_0013B500(void *object, int kind);
void func_001CBAA0(void *game, void *resource);
#define FLUSH_PAIR(object, other) \
    ((void (*)(void *, void *))(object)->vtable[58].method)((char *)(object) + (object)->vtable[58].delta, (other))
void func_001E53D8(struct FlushSelf *self)
{
    struct FlushNode *node;
    func_0023E068(self);
    if (func_001E5FF8(self))
        return;
    for (node = self->owner->head; node; node = node->next) {
        if (!node->link->occupant)
            continue;
        if (!func_001E4F40(self, node->object))
            continue;
        if (!(self->flags & 0x0300000000000000UL))
            func_001E5070(self, node->object, 0);
        if (func_0013B500(node->object, 0x6F)) {
            struct FlushObject *other = node->object;
            if (func_001E4F40(other, self))
                func_001E5070(other, self, 0);
        }
        FLUSH_PAIR(self, node->object);
        FLUSH_PAIR(node->object, self);
        func_001CBAA0(D_00475480, node->resource);
        node->link->occupant = 0;
        node->resource = 0;
    }
}

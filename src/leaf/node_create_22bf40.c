// SLY3_CFLAGS: -Os -G0
// Create a child node for an owner from a pool: zeroed 0x180-byte block, construct, link to owner/parent/resource, register
// in the owner's child list and run its first virtual hook.
struct VirtualEntry { short delta; short pad; void (*call)(void *); };
struct Spec { unsigned char pad00[4]; int resource; };
struct Owner { unsigned char pad00[0x48]; unsigned char children[0x10]; };
struct Node {
    unsigned char pad00[0xC]; struct VirtualEntry *vtable;
    unsigned char pad10[4]; struct Owner *owner; void *handle[1]; void *root; void *resource;
    unsigned char pad24[8]; struct Spec *spec;
    unsigned char pad30[0x88 - 0x30]; float f88;
    unsigned char pad8C[0x15C - 0x8C]; unsigned char list15C[0x20];
};
extern char D_00479D44[];
extern char D_00475480[];
extern float D_00326C3C;
void *func_0011E118(void *pool);
void *func_00292034(void *destination, int value, unsigned int bytes);
void func_002BF0C0(void *node);
void func_002BF050(void **handle, void *target);
void *func_0017E1B8(void *game, int kind, int index, void *argument);
void func_0011AF38(void *list, int count);
void func_0011AF90(void *list, void *item);
struct Node *func_0022BF40(struct Owner *owner, struct Spec *spec, struct Node *parent)
{
    struct Node *node = (struct Node *)func_0011E118(D_00479D44);
    func_00292034(node, 0, 0x180);
    func_002BF0C0(node);
    node->owner = owner;
    func_002BF050(node->handle, parent);
    if (parent)
        node->root = parent->root;
    else
        node->root = owner;
    if (spec->resource != -1)
        node->resource = func_0017E1B8(D_00475480, 5, spec->resource, 0);
    node->spec = spec;
    node->f88 = D_00326C3C;
    func_0011AF38(node->list15C, 8);
    func_0011AF90(owner->children, node);
    node->vtable[1].call((char *)node + node->vtable[1].delta);
    return node;
}

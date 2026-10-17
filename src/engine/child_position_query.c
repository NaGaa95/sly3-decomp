// SLY3_CFLAGS: -Os -G0
typedef int ChildVector __attribute__((mode(TI)));
struct ChildEntry { short delta; short pad; ChildVector *(*fn)(void *); };
struct ChildObject { unsigned char prefix[0xC]; struct ChildEntry *table; unsigned char gap[0x176C-0x10]; struct ChildObject *child; };
struct ChildHolder { unsigned char prefix[0x10]; struct ChildObject *owner; };
ChildVector func_00135080(struct ChildHolder *holder)
{
    struct ChildObject *owner=holder->owner;
    struct ChildObject *child=owner->child;
    if(!child) return *owner->table[36].fn((char *)owner+owner->table[36].delta);
    return *child->table[36].fn((char *)child+child->table[36].delta);
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CloneMethod { short delta, pad; void (*call)(void *); };
struct CloneChild {
    char prefix[0x18];
    struct CloneMethod *table;
};
struct CloneProperty {
    char prefix[0xD0];
    int count;
    struct CloneChild **children;
    char gapD8[8];
    void *parent, *space;
};
void func_0028FE20(void *destination, void *source);

void func_001FE550(void *destination, void *source)
{
    struct CloneProperty *property = destination;
    void *parent = property->parent;
    void *space = property->space;
    int index = 0;
    func_0028FE20(destination, source);
    property->parent = parent;
    property->space = space;
    for (; index < property->count; ++index) {
        struct CloneChild *child = property->children[index];
        struct CloneMethod *entry = &child->table[1];
        entry->call((char *)child + entry->delta);
    }
}

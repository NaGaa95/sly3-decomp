// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct DescriptorQueryEntry {
    short delta, pad;
    void *(*query)(void *receiver);
};
struct DescriptorChild {
    void *context;
    int key;
    char gap8[0x10];
    struct DescriptorQueryEntry *table;
};
struct DescriptorChildren {
    char prefix[0xD0];
    int count;
    struct DescriptorChild **children;
};

void *func_001FE950(void *receiver, int key)
{
    struct DescriptorChildren *property = receiver;
    int count = property->count;
    int index;
    for (index = 0; index < count; ++index) {
        struct DescriptorChild *child = property->children[index];
        if (child->key == key) {
            struct DescriptorQueryEntry *entry = &child->table[4];
            return entry->query((char *)child + entry->delta);
        }
    }
    return 0;
}

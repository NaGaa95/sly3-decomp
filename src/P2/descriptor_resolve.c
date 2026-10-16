// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ResolveMethod { short delta, pad; void (*call)(void *); };
struct ResolveChild {
    char prefix[0x18];
    struct ResolveMethod *table;
};
struct ResolveProperty {
    char prefix[0xC];
    struct ResolveMethod *table;
    char gap10[0xC0];
    int count;
    struct ResolveChild **children;
    int mode;
};
void func_001C7DC8(void *receiver);

void func_001FE5E0(void *receiver)
{
    struct ResolveProperty *property = receiver;
    int index;
    func_001C7DC8(receiver);
    if (property->mode == 0) {
        struct ResolveMethod *entry = &property->table[9];
        entry->call((char *)receiver + entry->delta);
    }
    for (index = 0; index < property->count; ++index) {
        struct ResolveChild *child = property->children[index];
        struct ResolveMethod *entry = &child->table[2];
        entry->call((char *)child + entry->delta);
    }
}

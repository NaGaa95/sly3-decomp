// SLY3_CFLAGS: -Os -G0
struct ActivationSlot { short delta, word2; void *method; };
struct ActivationEntry {
    unsigned char opaque00[0xC];
    struct ActivationSlot *methods;
};
extern unsigned char D_00475480[];
void *func_0017E1B8(void *game, int flags, int key, void *owner);

void *func_001D6980(void *owner, int key)
{
    struct ActivationEntry *entry = func_0017E1B8(D_00475480, 1, key, owner);
    if (entry)
        ((void (*)(void *))entry->methods[9].method)(
            (char *)entry + entry->methods[9].delta);
    return entry;
}

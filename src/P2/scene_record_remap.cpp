// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct SceneRemapEntry {
    char prefix[0x80];
    unsigned int word80, word84;
    unsigned int *pointer88, *pointer8C;
    char tail[0x100 - 0x90];
};
struct SceneRemapBank {
    char prefix[0x10];
    SceneRemapBank *parent;
    char pad14[0x40 - 0x14];
    int count;
    SceneRemapEntry *entries;
};
typedef char CheckRemapEntry100[sizeof(SceneRemapEntry) == 0x100 ? 1 : -1];
typedef char CheckRemapBank48[sizeof(SceneRemapBank) == 0x48 ? 1 : -1];

static inline int SceneRemapIndex(SceneRemapEntry *entry, SceneRemapEntry *base)
{
    return (int)((unsigned int)entry - (unsigned int)base) >> 8;
}

extern "C" void func_0023DDF0(SceneRemapBank *newBank, SceneRemapBank *oldBank,
                             SceneRemapEntry **slot)
{
    SceneRemapEntry *oldEntry = *slot;
    if (!oldEntry) return;
    SceneRemapEntry *newEntry = 0;
    int index = SceneRemapIndex(oldEntry, oldBank->entries);
    if (index >= 0 && index < newBank->count) {
        newEntry = &newBank->entries[index];
    } else {
        oldBank = oldBank->parent;
        index = SceneRemapIndex(oldEntry, oldBank->entries);
        if (index >= 0 && index < oldBank->count)
            newEntry = &newBank->parent->entries[index];
    }
    if (newEntry->pointer88 == &oldEntry->word80)
        newEntry->pointer88 = &newEntry->word80;
    if (newEntry->pointer8C == &oldEntry->word84)
        newEntry->pointer88 = &newEntry->word84;
    *slot = newEntry;
}

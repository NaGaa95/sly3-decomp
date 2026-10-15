// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ScenePairQueryEntry {
    short adjustment, reserved;
    int (*query)(void *);
};
struct ScenePairQueryFrame {
    char prefix[0xA0];
    int modeA0;
    char padA4[0xC0 - 0xA4];
    int modeC0;
};
struct ScenePairQueryState {
    char prefix[0xC];
    ScenePairQueryEntry *table;
    char pad10[0xD8 - 0x10];
    ScenePairQueryFrame *frame;
    char padDC[0x120 - 0xDC];
    unsigned long flags;
};
typedef char CheckPairQueryFrameC4[sizeof(ScenePairQueryFrame) == 0xC4 ? 1 : -1];
typedef char CheckPairQueryState128[sizeof(ScenePairQueryState) == 0x128 ? 1 : -1];

static inline int ScenePairQuery(ScenePairQueryState *object)
{
    ScenePairQueryEntry *entry = &object->table[66];
    return entry->query((char *)object + entry->adjustment);
}

extern "C" int func_0023E178(ScenePairQueryState *first, ScenePairQueryState *second)
{
    if (((first->flags & (1UL << 58)) || ScenePairQuery(first)) && ScenePairQuery(second))
        return 1;
    return 0;
}

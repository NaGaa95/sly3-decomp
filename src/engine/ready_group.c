// SLY3_CFLAGS: -Os -G0
struct ReadyGroup {
    char prefix[0x1A4];
    int count;
    void *entries[0];
};
int func_001710E0(void *receiver);
int func_00171868(struct ReadyGroup *group)
{
    int i;
    for (i = 0; i < group->count; ++i) {
        if (!func_001710E0(group->entries[i]))
            return 0;
    }
    return 1;
}

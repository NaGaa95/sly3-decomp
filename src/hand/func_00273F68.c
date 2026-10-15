// Select the first qualifying tuple of lowest rank; retain signed -1 for no match.
// Complete original inputs, signed return and boundaries were independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Entry {
    void *first;
    void *second;
    int mode;
};
struct Receiver {
    char prefix[0x168];
    int count;
    struct Entry entries[4];
};
int func_00273F68(struct Receiver *p, void *first, void *second) {
    int minimum = 0x7FFFFFFF;
    struct Entry *selected = 0;
    int i;
    for (i = 0; i < p->count; ++i) {
        struct Entry *entry = p->entries + i;
        if (!entry->first || entry->first == first || !entry->second || entry->second == second) {
            int rank = entry->first != first;
            if (entry->second != second)
                rank += 2;
            if (rank < minimum) {
                minimum = rank;
                selected = entry;
            }
        }
    }
    {
        if (!selected)
            return -1;
        return selected->mode != 0;
    }
}

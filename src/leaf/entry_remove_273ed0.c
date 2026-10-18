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
void func_001D2898(void *destination, const void *source, unsigned int bytes);
void func_00273ED0(struct Receiver *p, void *first, void *second, int mode) {
    int i;
    for (i = 0; i < p->count; ++i) {
        struct Entry *entry = p->entries + i;
        if (entry->first == first && entry->second == second && entry->mode == mode) {
            func_001D2898(entry, entry + 1, (p->count - 1 - i) * sizeof(struct Entry));
            --p->count;
            return;
        }
    }
}

// Keep the unique pointer/pointer/mode tuple in the four-entry receiver list.
// Complete original inputs and boundaries were independently reviewed.
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
void func_00273E48(struct Receiver *p, void *first, void *second, int mode) {
    int i;
    for (i = 0; i < p->count; ++i) {
        struct Entry *entry = p->entries + i;
        if (entry->first == first && entry->second == second && entry->mode == mode) return;
    }
    if ((unsigned int)p->count < 4) {
        struct Entry *entry = p->entries + p->count++;
        entry->first = first;
        entry->second = second;
        entry->mode = mode;
    }
}

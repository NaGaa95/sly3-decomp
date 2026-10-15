// Set the original entry and linked-record flags for kinds two and three.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int FLAGS64 __attribute__((mode(DI)));
struct Linked {
    char prefix[0x10];
    FLAGS64 flags;
};
struct Entry {
    char prefix[0xC];
    unsigned int tag;
    char gap10[0x14];
    struct Linked *linked;
};
struct Receiver {
    char prefix[0xA8];
    int count;
    int gapAC;
    struct Entry *entries;
};
void func_0023FF30(struct Receiver *p) {
    int i;
    for (i = 0; i < p->count; ++i) {
        struct Entry *entry = p->entries + i;
        unsigned int tag = entry->tag;
        if ((tag & 7) == 2 || (tag & 7) == 3) {
            entry->tag = tag | 0x1000;
            if (entry->linked) entry->linked->flags |= (FLAGS64)1 << 50;
        }
    }
}

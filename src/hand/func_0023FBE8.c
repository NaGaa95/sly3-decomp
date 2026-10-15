// Return the first kind-two linked node from the original record array, with optional integer-key filtering.
// Complete original inputs, boundaries and initialized sections are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Node {
    int kind;
    char gap4[0xC];
    struct Node *next;
};
struct Entry {
    char prefix[0x90];
    struct Node *head;
    char gap94[8];
    int key;
    char tailA0[0x60];
};
struct Receiver {
    char prefix[0x40];
    int count;
    struct Entry *entries;
};
struct Node *func_0023FBE8(struct Receiver *p, int key) {
    int i;
    for (i = 0; i < p->count; ++i) {
        struct Entry *entry = p->entries + i;
        if (key == -1 || key == entry->key) {
            struct Node *node;
            for (node = entry->head; node; node = node->next) if (node->kind == 2) return node;
        }
    }
    return 0;
}

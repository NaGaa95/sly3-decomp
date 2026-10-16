// SLY3_CFLAGS: -Os -G0
union RecordSearchHeader {
    unsigned int word;
    unsigned char kind;
};
struct RecordSearchEntry {
    union RecordSearchHeader header;
    int unused4;
    int key;
    int unusedC;
};
struct RecordSearchResource {
    unsigned char prefix[0x44];
    struct RecordSearchEntry *entries;
};
struct RecordSearchContext {
    unsigned char prefix[0x14];
    struct RecordSearchResource *resource;
    unsigned char unknown18[0x2C - 0x18];
    struct RecordSearchEntry *root;
    unsigned char unknown30[0x118 - 0x30];
    int depth;
    struct RecordSearchEntry *path[0];
};
typedef char RecordSearchEntrySize[sizeof(struct RecordSearchEntry)==16?1:-1];
typedef char RecordSearchPathPrefix[sizeof(struct RecordSearchContext)==0x11C?1:-1];

static __inline__ struct RecordSearchEntry *RecordSearchIndex(
    struct RecordSearchResource *resource, unsigned int index)
{
    return index ? &resource->entries[index] : 0;
}

void *func_00226828(void *raw_context, void *raw_entry, int key)
{
    struct RecordSearchContext *context = raw_context;
    struct RecordSearchEntry *entry = raw_entry;
    if (entry == context->root) {
        context->depth = 1;
        context->path[0] = entry;
        entry = RecordSearchIndex(context->resource, (entry->header.word >> 9) & 0x7FF);
    }
    for (; entry; entry = RecordSearchIndex(context->resource,
                          (entry->header.word >> 20) & 0x7FF)) {
        if (entry->header.kind != 0) {
            struct RecordSearchEntry *child;
            if (entry->header.kind == 0x20 && entry->key == key)
                return entry;
            child = RecordSearchIndex(context->resource, (entry->header.word >> 9) & 0x7FF);
            if (child) {
                void *selected;
                context->path[context->depth++] = entry;
                selected = func_00226828(context, child, key);
                if (selected)
                    return selected;
                if (context->depth)
                    --context->depth;
            }
        }
    }
    return 0;
}

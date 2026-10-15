// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
// Partial physical views; each entry is eight bytes and its first word is an ID.
struct Entry {
    int identifier;
    unsigned char opaque4[4];
};
struct List {
    char prefix[0x44];
    struct Entry *entries;
};
struct Request {
    char prefix[0x24];
    struct List *list;
    char padding[0x34-0x28];
    int requested_index;
    int pending_index;
};
int func_00239E90(struct Request *request) {
    int index = request->pending_index;
    if (index >= 0) return request->list->entries[index].identifier;
    index = request->requested_index;
    if (index >= 0) return request->list->entries[index].identifier;
    return -1;
}

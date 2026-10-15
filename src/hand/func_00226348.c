// Find the first record-key node except the excluded pointer, preserving the original empty cleanup lifetime.
// Complete original inputs, return and boundaries were independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Record {
    char prefix[4];
    int key;
};
struct Node {
    char prefix[0x2C];
    struct Record *record;
    char pad[0x10C-0x30];
    struct Node *next;
};
struct Receiver {
    char prefix[0x48];
    struct Node *head;
};
// Original empty cleanup consumes flags only. Its flag2 path reads no object storage.
struct EmptyCleanup {
    char unused;
};
void func_002BF118(void *object,int flags);
struct Node *func_00226348(struct Receiver *receiver,int key,struct Node *excluded) {
    struct EmptyCleanup cleanup;
    struct Node *node;
    for(node=receiver->head;node;node=node->next) {
        if(node != excluded && node->record->key == key) {
            func_002BF118(&cleanup,2);
            return node;
        }
    }
    func_002BF118(&cleanup,2);
    return 0;
}

// SLY3_CFLAGS: -Os -G0
struct PointerLookupNode {
    void *unaccessed0;
    void *key;
    char unaccessed8[0x160-8];
    struct PointerLookupNode *next;
};
extern struct PointerLookupNode *D_00479BF8;
void func_002BC468(void *scope, int flags);
void *func_0014BB50(void *key)
{
    struct PointerLookupNode *node;
    unsigned char scope;
    for (node = D_00479BF8; node; node = node->next) {
        if (node->key == key) {
            func_002BC468(&scope, 2);
            return node;
        }
    }
    func_002BC468(&scope, 2);
    return 0;
}

typedef int MatrixCopyQword __attribute__((mode(TI)));
struct SnapshotMatrix { MatrixCopyQword row[4]; };
struct MatrixSnapshotState {
    char prefix[0x50];
    struct SnapshotMatrix current;
    char unaccessed90[0x118-0x90];
    float radius;
    char unaccessed11C[0x2A4-0x11C];
    int absent;
    char unaccessed2A8[8];
    struct SnapshotMatrix saved;
    float saved_radius;
};
void func_001C7DC8(void *receiver);
void func_001C9118(void *receiver, int state);
int func_00165DC8(void *receiver);
void func_00165A48(struct MatrixSnapshotState *p)
{
    func_001C7DC8(p);
    func_001C9118(p, 2);
    p->saved_radius = p->radius;
    p->saved = p->current;
    p->absent = func_00165DC8(p);
}

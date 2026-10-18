// SLY3_CFLAGS: -Os -G0
struct RequestEntry {
    short delta;
    short unused;
    void (*call)(void *);
};
struct RequestObject {
    unsigned char prefix[0xC];
    struct RequestEntry *table;
    unsigned char gap10[0x38];
    int state;
    unsigned char gap4C[0x14];
    int second;
    int first;
    int third;
    int appliedSecond;
};
void func_00261070(void *object, int state);
void func_00261050(void *object, int state);
void func_00260F18(struct RequestObject *object, int first, int second, int third)
{
    if (!object->state)
        func_00261070(object, 1);
    func_00261050(object, 2);
    object->third = third;
    object->first = first;
    object->second = second;
    if (first == -1) {
        if (object->state != 2 || object->appliedSecond != second) {
            func_00261070(object, 1);
            func_00261070(object, 2);
        }
    } else if (object->state == 1) {
        struct RequestEntry *entry = &object->table[18];
        entry->call((char *)object + entry->delta);
    }
}

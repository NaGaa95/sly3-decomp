// Clear the trailing field of the receiver and re-register the receiver with the global collection.
// SLY3_CFLAGS: -Os -G0
struct EntryList {
    char opaque000[0x130];
    unsigned int count;
    int entries[7];
    int cleared;
};
extern char D_00475480[];
void func_0013CD10(void *list, void *object);

void func_00223858(struct EntryList *object)
{
    object->cleared = 0;
    func_0013CD10(D_00475480, object);
}

// Append an entry to the receiver's fixed seven-slot list; ignore it when the list is full.
// SLY3_CFLAGS: -Os -G0
struct EntryList {
    char opaque000[0x130];
    unsigned int count;
    int entries[7];
    int cleared;
};

void func_00223888(struct EntryList *object, int entry)
{
    if (object->count < 7) {
        object->entries[object->count++] = entry;
    }
}

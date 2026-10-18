// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct FocusLink {
    unsigned char opaque00[0x60];
    int id;
};
struct FocusEntry {
    unsigned char opaque00[0x4C];
    int id;
    unsigned char opaque50[0x6C - 0x50];
    FocusLink *link;
};
struct FocusGame {
    unsigned char opaque00[0x4044];
    FocusLink *current;
};
struct FocusRecord {
    unsigned char opaque00[0xBC];
    int ids[2];
};
struct FocusSelf {
    unsigned char opaque00[8];
    FocusRecord *record;
};
extern "C" {
extern unsigned char D_00475480[];
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void func_0018A900(int *count, FocusEntry ***list);
int func_00188A38(FocusEntry *entry);

void func_001BE918(FocusSelf *self)
{
    FocusRecord *record = self->record;
    if (!record)
        return;
    record->ids[0] = record->ids[1] = -1;
    FocusLink *current = ((FocusGame *)D_00475480)->current;
    if (!current)
        return;
    int id = current->id;
    if (id == -1)
        return;
    int slot = 1;
    int i = 0;
    void *frame;
    int count;
    FocusEntry **list;
    self->record->ids[0] = id;
    func_001D2770(&frame);
    func_0018A900(&count, &list);
    while (i < count) {
        FocusEntry *entry = list[i];
        if (((FocusGame *)D_00475480)->current == entry->link && entry->id != -1 &&
            !func_00188A38(entry)) {
            self->record->ids[slot] = entry->id;
            break;
        }
        i++;
    }
    func_001D2798(&frame, 2);
}
}

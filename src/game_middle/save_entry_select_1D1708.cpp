// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
struct SaveEntry { unsigned char data[0x6864]; };
struct EntrySaveView {
    unsigned char opaque00[8];
    int mode;
    unsigned char opaque0C[0x24 - 0x0C];
    SaveEntry entries[1];
};
struct EntrySaveTail {
    unsigned char opaque00[0x13958];
    void *pendingEntry;
};
struct EntryMenuView {
    unsigned char opaque00[0x58];
    int selection;
};
struct EntrySource { unsigned char opaque00[8]; int index; unsigned char opaque0C[0x1C - 0x0C]; unsigned int flags; };
struct KEY;
class EntryReadyReference {
public:
    CRef value;
    EntryReadyReference(const EntryReadyReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~EntryReadyReference() { Drop(); }
};
extern "C" {
extern unsigned char D_00375290[], D_003751D0[];
extern KEY *D_004794EC;
EntryReadyReference QueryEntryReady(KEY *, unsigned char *) __asm__("func_002BC010");
void func_001D0C08(void *menu, int mode);
void func_001D1648(void);
}
extern "C" void func_001D1708(EntrySource *source)
{
    EntrySaveView *save = (EntrySaveView *)D_00375290;
    if (save->mode == 6) {
        EntryMenuView *menu = (EntryMenuView *)D_003751D0;
        if (menu->selection == 1) {
            SaveEntry *entries = save->entries;
            SaveEntry *entry = entries + source->index;
            float ready = QueryEntryReady(D_004794EC, (unsigned char *)entry).value.payload.real;
            ((EntrySaveTail *)save)->pendingEntry = entry;
            if (ready == 0.0f)
                func_001D1648();
            else
                func_001D0C08(menu, 0x28);
        }
    }
    if (source)
        source->flags |= 2;
}

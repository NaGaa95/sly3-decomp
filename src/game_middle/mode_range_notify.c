// SLY3_CFLAGS: -Os -G0
struct ModeEntry { int mode; };
struct ModeOwner {
    unsigned char prefix[4];
    int id;
    unsigned char gap[0x30 - 8];
    struct ModeEntry *entry;
};
void func_001BDBB0(void *, int);
void func_001BDB50(struct ModeOwner *owner)
{
    struct ModeEntry *entry = owner->entry;
    if (entry) {
        int mode = entry->mode;
        if (mode == 0)
            return;
        if (mode >= 0) {
            if (mode < 11) {
                if (mode >= 8)
                    return;
            }
        }
    }
    if (owner->id != -1)
        func_001BDBB0(owner, 2);
}

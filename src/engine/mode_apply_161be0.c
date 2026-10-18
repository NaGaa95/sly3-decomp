// SLY3_CFLAGS: -Os -G0
struct ModeEntry { short delta, padding; int (*fn)(void *); };
struct ModeTable { int slot0, slot1; struct ModeEntry entry; };
struct ModeSource { struct ModeTable *table; };
struct ModeOwner { unsigned char prefix[0x18AC]; struct ModeSource *source; };
int func_002533C0(void *owner, int index);
int func_001F4458(void *owner);
void func_001F4438(void *owner, int value);
void func_00161C60(void *owner, int mode);
void func_00161BE0(struct ModeOwner *owner)
{
    if(func_002533C0(owner, 0x42)) {
        struct ModeSource *source = owner->source;
        if(source) {
            int mode = source->table->entry.fn((char *)source + source->table->entry.delta);
            func_001F4438(owner, func_001F4458(owner));
            func_00161C60(owner, mode);
        }
    }
}

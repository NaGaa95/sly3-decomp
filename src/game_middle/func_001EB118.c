// SLY3_CFLAGS: -Os -G0
struct Clock { float time; };
struct Source { void *kind; };
struct Owner { unsigned char prefix[0x14]; struct Source *source; };
struct Entry { struct Owner *owner; void *object; float time; };
struct Tracker {
    unsigned char prefix0[0x16B0];
    struct Entry entries[4];
    int count;
    unsigned char gap16E4[0x16F4 - 0x16E4];
    void *resource;
};
extern struct Clock D_0036BB98;
void *func_001EB058(void *resource);
int func_0013B500(void *object, int kind);
void *func_00291F38(void *destination, const void *source, unsigned int bytes);
void func_001552D8(void *tracker, int mode, void *owner);

void func_001EB118(struct Tracker *tracker, struct Owner *owner)
{
    int i;
    void *kind = owner->source->kind;
    if ((unsigned int)tracker->count < 4) {
        void *object = func_001EB058(tracker->resource);
        struct Entry *entry;
        if (!object)
            return;
        entry = &tracker->entries[tracker->count++];
        entry->object = object;
        entry->owner = owner;
        entry->time = D_0036BB98.time;
        func_001552D8(tracker, 4, owner);
    } else if (func_0013B500(kind, 0x3A)) {
        for (i = 0; i < tracker->count; i++) {
            struct Entry *entry = &tracker->entries[i];
            if (!func_0013B500(entry->owner->source->kind, 0x3A)) {
                void *object = entry->object;
                func_00291F38(entry, entry + 1, (tracker->count - i) * sizeof(struct Entry) - sizeof(struct Entry));
                entry = &tracker->entries[tracker->count - 1];
                entry->object = object;
                entry->owner = owner;
                entry->time = D_0036BB98.time;
                func_001552D8(tracker, 4, owner);
                return;
            }
        }
    }
}

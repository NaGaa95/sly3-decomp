// SLY3_CFLAGS: -Os -G0
struct QueueEntry { float value; int word4; float time; int zeroC, zero10, zero14, zero18; };
struct QueueSelf { unsigned char prefix0[0x3C0]; int count; struct QueueEntry entries[3]; };
extern char D_00474FF0[];
float func_002483D8(void *context);
void *func_00291F38(void *destination, void *source, int bytes);
void func_0020A880(struct QueueSelf *self, int word, float value)
{
    struct QueueEntry *entry;
    if (self->count == 3) {
        func_00291F38(&self->entries[0], &self->entries[1], (self->count - 1) * sizeof(struct QueueEntry));
        entry = &self->entries[self->count - 1];
    } else {
        entry = &self->entries[self->count++];
    }
    entry->value = value;
    entry->word4 = word;
    entry->time = func_002483D8(D_00474FF0);
    entry->zeroC = 0;
    entry->zero10 = 0;
    entry->zero14 = 0;
    entry->zero18 = 0;
}

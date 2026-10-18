// SLY3_CFLAGS: -Os -G0 -fno-gcse
struct PaletteEntry { long value; int kind; int pad; } __attribute__((aligned(16)));
struct PaletteSource { unsigned char prefix[6]; short flags; unsigned char shades[4]; int count; long *items; };
struct PaletteSelf {
    unsigned char prefix[0x190]; int size; unsigned char gap194[0x1A0 - 0x194]; struct PaletteEntry entries[32];
    int ready; unsigned char shades[4]; unsigned char gap3A8[0x428 - 0x3A8]; void *table;
};
extern unsigned char D_0036B2E0[];
extern unsigned char D_0036B2A0[];
struct PaletteSource *func_00235F40(int id);
void func_001498C0(struct PaletteSelf *self, int id)
{
    struct PaletteSource *source = func_00235F40(id);
    int count, size, extra, i, shift, k;
    int f;
    struct PaletteEntry *entry;
    f = source->flags;
    self->table = (f & 1) ? D_0036B2E0 : D_0036B2A0;
    if(!self->ready) {
        self->ready = 1;
        for(i = 0; i < 4; i++) self->shades[i] = (source->shades[i] + 1) >> 1;
    }
    count = source->count;
    extra = 0;
    size = 1;
    for(shift = count >> 1; shift; shift >>= 1) size <<= 1;
    size <<= (size < count);
    while(size >= 0x20) size >>= 1;
    if(count < size) extra = size - count;
    self->size = size;
    entry = self->entries;
    for(k = 0; k < count; k++) {
        entry->value = source->items[k];
        entry->kind = 6;
        if(k < extra) {
            entry[1] = entry[0];
            entry++;
        }
        entry++;
    }
}

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Load one table through the shared loader, convert its 4-byte entries (halve with rounding up),
// reverse their order and shrink the allocation to the entry count.
struct FRAME { int pad[4]; FRAME(); ~FRAME(); };   // out-of-line ctor/dtor 0x1D2770 / 0x1D2798
struct ALLOCREQ { int cb; int cbAlign; };
struct ENTRY4 { unsigned char b[4]; };
struct TABLE {
    unsigned char prefix[0x218];
    int count;
    ENTRY4 entries[1];
};
struct LOADED { unsigned char prefix[0x20]; TABLE *table; };
struct LINK { unsigned char prefix[0x1C]; LOADED *loaded; };
struct LOAD_OWNER { unsigned char prefix[0x20]; LINK *link; };
extern "C" {
void *func_001D2670(ALLOCREQ *);
void *func_001D24D0(ALLOCREQ *, void *);
void func_001FD198(void *, void *);
void func_00236908(void *);
}
static inline ALLOCREQ *Request(ALLOCREQ *request, int cb, int cbAlign)
{
    request->cb = cb;
    request->cbAlign = cbAlign;
    return request;
}
static inline void Swap(ENTRY4 *a, ENTRY4 *b, ENTRY4 *t) { *t = *a; *a = *b; *b = *t; }
extern "C" void func_001FD9D8(LOAD_OWNER *owner, void *stream)
{
    LOADED *loaded = owner->link->loaded;
    FRAME frame;
    int bytes = sizeof(TABLE);
    union { ALLOCREQ request; ENTRY4 temp; } u;
    loaded->table = (TABLE *)func_001D2670(Request(&u.request, 0x29C, 16));
    *(int *)loaded->table = -1;
    func_001FD198(owner, stream);
    TABLE *table = loaded->table;
    int count = table->count;
    if (count) {
        ENTRY4 *entries = table->entries;
        bytes = sizeof(TABLE) + (count - 1) * sizeof(ENTRY4);
        for (int i = 0; i < count; i++) {
            ENTRY4 *entry = &entries[i];
            func_00236908(entry);
            for (int j = 0; j < 4; j++)
                entry->b[j] = (entry->b[j] + 1) >> 1;
        }
        ENTRY4 *lo = entries;
        ENTRY4 *hi = &entries[count] - 1;
        while (lo < hi)
            Swap(lo++, hi--, &u.temp);
    }
    TABLE *old = loaded->table;
    loaded->table = (TABLE *)func_001D24D0(Request(&u.request, bytes, 16), old);
}

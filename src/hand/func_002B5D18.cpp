// Construct the original base, forty-eight inline command entries, and the embedded tail in existing storage.
// Original accessed layouts and complete argument flow are independently verified; nominal type names remain provisional.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Placement new has its standard size/storage parameters; only existing storage is used.
inline void *operator new[](unsigned int bytes,void *storage) {
    return storage;
}
struct Entry {
    char bytes[0x20];
    Entry() __asm__("func_002B8840");
};
struct Tail {
    char bytes[0x10];
};
struct S {
    char prefix[0xC];
    const void *vtable;
    char gap[0x4D0];
    Entry entries[48];
    char gap2[0x4E0];
    Tail tail;
};
extern "C" void *func_002B5AA8(void *receiver);
extern "C" void *func_002B5958(void *receiver);
extern char D_00366690[];
extern "C" S *func_002B5D18(S *p) {
    func_002B5AA8(p);
    p->vtable=D_00366690;
    new(p->entries)Entry[48];
    func_002B5958(&p->tail);
    return p;
}

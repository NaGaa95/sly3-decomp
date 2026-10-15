// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { char data[0x50]; }; struct Owner { char pad[0xC]; int first; char pad2[0x68-0x10]; struct Entry *entries; }; struct Object { char pad[0xD0]; struct Owner *owner; }; struct Entry *func_001FB600(struct Object *p,int index) { struct Owner *owner = p->owner; return owner->entries + (index - owner->first); }

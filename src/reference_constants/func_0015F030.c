// Reference algorithm: src/hand/func_00120820.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { int a,b,value; }; struct Owner { char pad[0x48]; struct Entry *entries; }; struct Object { char pad[0x38]; struct Owner *owner; int index; }; int func_0015F030(struct Object *p) { return p->owner->entries[p->index].value; }

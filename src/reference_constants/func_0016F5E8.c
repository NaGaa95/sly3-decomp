// Reference algorithm: src/hand/func_001FD0C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { char pad[0x40]; int value; int reserved; }; struct Object { char pad[0x44]; struct Entry *entries; char pad2[0x698-0x48]; int index; }; int func_0016F5E8(struct Object *p) { if(p->index < 0) return -1; return p->entries[p->index].value; }

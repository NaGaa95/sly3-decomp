// Complete original Sly3 body; ordinary source/profile reconstruction.
// A0 owner at0xD0 supplies the array base0x68 and initial index0xC; A1 is an80-byte entry pointer. Both pointer difference and initial index are ordinary C.
// SLY3_CFLAGS: -Os -G0
struct Entry { char data[0x50]; }; struct Owner { char pad[0xC]; int first; char pad2[0x68-0x10]; struct Entry *entries; }; struct Object { char pad[0xD0]; struct Owner *owner; }; int func_001FB5D8(struct Object *p,struct Entry *entry) { struct Owner *owner=p->owner; return (entry-owner->entries)+owner->first; }

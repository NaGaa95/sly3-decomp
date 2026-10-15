// Reference algorithm: src/hand/func_00174920.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void func_001A9878(struct S *p, void *owner);
void func_001A99D0(void *, void *);
void func_00171508(struct S *p, void *owner) { func_001A9878(p, owner); func_001A99D0((char *)p + 0x1D4, *(void **)((char *)p + 0x134)); }

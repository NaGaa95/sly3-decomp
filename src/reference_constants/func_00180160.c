// Reference algorithm: src/hand/func_00174920.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void func_00238980(struct S *p);
void func_00252FC0(void *, int);
void func_00180160(struct S *p) { func_00238980(p); func_00252FC0(*(void **)((char *)p + 0x10), 0x38); }

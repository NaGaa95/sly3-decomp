// Reference algorithm: src/hand/func_00174920.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void func_001C7340(struct S *p);
void func_0011AD60(void *, int);
void func_00197168(struct S *p) { func_001C7340(p); func_0011AD60((char *)p + 0x40, 0x1C); }

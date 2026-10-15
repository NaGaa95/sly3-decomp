// Reference algorithm: src/hand/func_00174920.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void func_001C7340(struct S *p);
void func_001C9118(void *, int);
void func_001771F0(struct S *p) { func_001C7340(p); func_001C9118(p, 1); }

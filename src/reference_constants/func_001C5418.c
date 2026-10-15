// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; void func_001C5C18(void *,void *);
void func_001C85E8(void *p);
void func_001C5418(char *p) { func_001C85E8(p); func_001C5C18(D_00475480, p); }

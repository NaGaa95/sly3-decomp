// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00479B98[]; void func_0011B028(void *,void *);
void func_001C7938(void *p);
void func_00177258(char *p) { func_001C7938(p); func_0011B028(D_00479B98, p); }

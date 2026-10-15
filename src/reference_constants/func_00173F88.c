// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00479B80[]; void func_0011AF60(void *,void *);
void func_001C78A0(void *p);
void func_00173F88(char *p) { func_001C78A0(p); func_0011AF60(D_00479B80, p); }

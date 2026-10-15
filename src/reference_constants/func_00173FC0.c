// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00479B80[]; void func_00174048(void *,int); void func_0011B028(void *,void *);
void func_001C7938(void *p); void func_00173FC0(char *p) { func_001C7938(p); func_00174048(p, 1); func_0011B028(D_00479B80, p); }

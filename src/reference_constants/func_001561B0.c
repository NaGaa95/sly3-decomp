// Reference algorithm: src/hand/func_001F3868.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[]; void *func_00185720(void *,void *); void func_00155E30(void *,int); void func_001561B0(void *p) { char *entry = func_00185720(D_0036C700, p); func_00155E30(p, *(int *)(entry + 8)); }

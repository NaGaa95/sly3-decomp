// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_001961D0(void *,int); void func_00196298(void *,void *); void func_00196228(char *p,int kind) { *(int *)p = kind; func_00196298(p, func_001961D0(p, kind)); }

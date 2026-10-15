// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_001750B0(int input); void func_00168AB0(void *,int,int,void *); void func_00175208(int input,void *unused1,void *p) { func_00168AB0(func_001750B0(input), 2, 2, p); }

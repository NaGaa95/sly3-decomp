// Reference algorithm: src/hand/func_001F7530.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00172C30(void *,int); void *func_00172A90(void *,int); void func_00172E60(void *,void *); void func_00173280(void *,int); void func_00172D10(void *p,int index) { func_00172C30(p,index); func_00172E60(p,func_00172A90(p,index)); func_00173280(p,-1); }

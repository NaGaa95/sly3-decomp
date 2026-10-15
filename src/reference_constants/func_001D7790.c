// Reference algorithm: src/hand/func_0012E6E8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00238980(void *); void func_001D77E0(void *,int,void *); void func_00252FC0(void *,int); void func_001D7790(char *p) { func_00238980(p); func_001D77E0(p,-1,0); if(*(int *)(p+0x38)!=-1)func_00252FC0(*(void **)(p+0x10),*(int *)(p+0x38)); }

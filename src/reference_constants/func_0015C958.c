// Reference algorithm: src/hand/func_001B3190.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0015BF28(void *); void *func_002459F8(int); void func_00244F08(void *,void *); void func_0015C958(char *p) { func_0015BF28(p+0x130); if(*(int *)(p+0x224)!=-1)func_00244F08(func_002459F8(*(int *)(p+0x224)),p); }

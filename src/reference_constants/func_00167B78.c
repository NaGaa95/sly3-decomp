// Reference algorithm: src/hand/func_00119C08.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00167AB0(void *,int,int,int,int); void func_00167B78(char *p,int value) { func_00167AB0(p, *(int *)(p + 0x160), value, *(int *)(p + 0x168), *(int *)(p + 0x16C)); }

// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001F4430(void *); void func_001F4438(void *,int); void func_001F4460(char *p,int value) { *(int *)(p + 0x178) = value; func_001F4438(p, func_001F4430(p)); }

// Reference algorithm: src/hand/func_00228BB0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001591E8(void *,int);
void func_00238980(void *p); void func_00158E10(char *p) { func_00238980(p); func_001591E8(p, -1); *(int *)(*(char **)(p + 0x10) + 0x11B8) &= ~1; }

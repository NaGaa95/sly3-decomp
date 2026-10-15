// Reference algorithm: src/hand/func_001BBEA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0016CB38(void *,int); void func_00252FC0(void *,int); void func_002BC760(void *,int); void func_00240DB0(void *);
void func_00238980(void *p); void func_0016C9C0(char *p) { func_00238980(p); func_0016CB38(p, -1); func_00252FC0(*(void **)(p + 0x10), *(int *)(p + 0x40)); func_002BC760(p + 0x30, 0); func_00240DB0(*(void **)(p + 0x10)); }

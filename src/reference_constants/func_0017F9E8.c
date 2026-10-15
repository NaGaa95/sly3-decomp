// Reference algorithm: src/hand/func_001D4EC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0017FE90(void *,int); void func_00170360(void *); void func_00252FC0(void *,int);
void func_00238980(void *p); void func_0017F9E8(char *p) { func_00238980(p); func_0017FE90(p, -1); func_00170360(*(void **)(*(char **)(p + 0x10) + 0x10D0)); func_00252FC0(*(void **)(p + 0x10), 0x3C); }

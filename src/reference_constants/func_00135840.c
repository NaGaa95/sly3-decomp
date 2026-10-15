// Reference algorithm: src/hand/func_001D4EC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00135A50(void *,int); void func_00252FC0(void *,int); void func_00259D50(void *);
void func_00238980(void *p); void func_00135840(char *p) { func_00238980(p); func_00135A50(p, -1); func_00252FC0(*(void **)(p + 0x10), 0x21); func_00259D50(*(char **)(p + 0x10) + 0x4B0); }

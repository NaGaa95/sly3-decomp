// Reference algorithm: src/hand/func_00181598.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00171538(void *,int); void func_00171670(void *,int);
void func_001F3C48(void *p); void func_00171138(char *p) { func_001F3C48(p); func_00171538(p, -1); func_00171538(p, *(void **)(p + 0x1C8) != 0); func_00171670(p, -1); }

// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C668[]; void func_0011B028(void *,void *); void func_0011AF60(void *,void *); void func_001495F8(char *p) { func_0011B028(*(void **)(p + 0x108C), p); func_0011AF60(D_0036C668, p); }

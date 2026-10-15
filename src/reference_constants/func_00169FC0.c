// Reference algorithm: src/hand/func_0020CE40.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00167960(void *,float); void func_00169FC0(char *p) { *(int *)(p + 0x34) = 0; *(int *)(p + 0x38) = 0; func_00167960(*(void **)p, *(float *)(p + 0x40)); }

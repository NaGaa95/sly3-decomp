// Reference algorithm: src/hand/func_001EECD0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0016AE90(void *); void func_0016AE00(char *p,int value) { *(int *)(p + 0x24) = value; if (*(int *)(p + 0x50)) func_0016AE90(p); *(int *)(p + 0x50) = 0; }

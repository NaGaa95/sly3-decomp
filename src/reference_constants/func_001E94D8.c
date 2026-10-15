// Reference algorithm: src/hand/func_001752C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

void func_00152720(void *p);
void func_001E94D8(char *p) { func_00152720(p); *(int *)(p + 0x16EC) = 0; }

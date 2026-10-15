// Reference algorithm: src/hand/func_0014D8D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00166548(char *p) { int value = 1; if(value < *(int *)(p + 0x2F4)) value = *(int *)(p + 0x2F4); *(int *)(p + 0x2F4) = value; }

// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001FF4C0(char *p) { int value = *(short *)(*(char **)(p + 4) + 0xA); *(int *)(p + 0x20) = 0; *(int *)(p + 0x14) = value; }

// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001FD4D0(char *p,int value) { *(short *)(*(char **)(p + 0x20) + 8) = value; }

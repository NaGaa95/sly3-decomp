// Reference algorithm: src/hand/func_00120370.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001A9918(char *p,unsigned int flags) { unsigned int old = *(unsigned int *)(p + 0x18); unsigned int pending = *(unsigned int *)(p + 0x30); *(unsigned int *)(p + 0x18) = old | flags; *(unsigned int *)(p + 0x30) = pending | (flags & ~old); }

// Reference algorithm: src/hand/func_001FE5B8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001A9940(char *p,unsigned int flags) { unsigned int active = *(unsigned int *)(p + 0x18); unsigned int pending = *(unsigned int *)(p + 0x30); *(unsigned int *)(p + 0x18) = active | flags; *(unsigned int *)(p + 0x30) = pending | flags; }

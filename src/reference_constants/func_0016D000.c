// Reference algorithm: src/hand/func_00155560.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

void func_0016C950(void *p);
void func_0016D000(char *p) { func_0016C950(p); *(void **)(p + 0x3C) = *(char **)(p + 0x10) + 0xC80; *(int *)(p + 0x40) = 5; }

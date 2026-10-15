// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0017F560(void *);
void func_00154FD8(void *p);
void func_0013F930(char *p) { func_00154FD8(p); if (*(int *)(p + 0x1520) == 0x10) func_0017F560(p + 0x1830); }

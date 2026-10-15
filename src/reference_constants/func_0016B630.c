// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00166548(void *);
void func_00169E40(void *p);
void func_0016B630(char *p) { func_00169E40(p); if (*(unsigned int *)(*(char **)(p + 0x160) + 0x7C) & 0x20) func_00166548(*(void **)p); }

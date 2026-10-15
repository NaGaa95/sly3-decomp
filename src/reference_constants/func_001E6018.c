// Reference algorithm: src/hand/func_0017EE78.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { char data[16]; }; int func_001E5FC8(void *); struct Entry *func_001E6018(char *p) { if (!func_001E5FC8(p)) return 0; return ((struct Entry *)*(void **)(p + 0x144)) + *(int *)(p + 0x13C); }

// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -O2 -G0
void *func_00165B28(char *p) { if (!*(void **)(p + 0x3EB8)) return 0; else return *(void **)(p + 0x3EBC); }

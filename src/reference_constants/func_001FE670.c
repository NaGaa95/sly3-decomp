// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0011B028(void *,void *);
void func_001C85C0(void *p); void func_001FE670(char *p) { func_001C85C0(p); if (*(int *)(p + 0xD8) == 2) func_0011B028(*(void **)(p + 0xF4), p); }

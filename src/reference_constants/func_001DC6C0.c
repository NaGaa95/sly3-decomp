// Reference algorithm: src/hand/func_00182E80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

void func_0023AE08(void *p);
void func_001DC6C0(char *p) { func_0023AE08(p); *(unsigned long *)(p + 0x128) &= ~8UL; }

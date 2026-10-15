// Reference algorithm: src/hand/func_001752C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

void func_001C7938(void *p);
void func_0017D248(char *p) { func_001C7938(p); *(int *)(p + 0x60) = 0; }

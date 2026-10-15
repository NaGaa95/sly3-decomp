// Reference algorithm: src/hand/func_0017CAC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

void func_001D8008(void *p);
void func_001D8BA8(char *p) { func_001D8008(p); *(int *)(p + 0xB0) = 14; *(float *)(p + 0xB4) = 1.0f; *(float *)(p + 0xD0) = 1.5f; }

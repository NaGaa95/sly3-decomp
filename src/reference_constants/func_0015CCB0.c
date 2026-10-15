// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

void func_0027F158(void *p, void *context);
void func_0015CCB0(char *p, void *context) { func_0027F158(p, context); if (*(void **)(p + 0x244)) *(int *)(p + 0x12C) = 1; }

// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00156FB8(char *p,int value) { *(int *)p = value; *(float *)(p + 4) = 1.0f; }

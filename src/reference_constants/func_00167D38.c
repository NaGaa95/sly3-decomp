// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern float D_0036BB98; void func_00167D38(char *p,int value) { float time = D_0036BB98; *(int *)(p + 0x360) = value; *(float *)(p + 0x35C) = time; }

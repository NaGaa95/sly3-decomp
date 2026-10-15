// Reference algorithm: src/hand/func_00155560.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
float func_0011E940(float,float);
void func_001F6798(void *p);
void func_001F9188(char *p) { func_001F6798(p); *(int *)(p + 0x1A8) = (int)func_0011E940(*(float *)(p + 0x1A0), *(float *)(p + 0x1A4)); }

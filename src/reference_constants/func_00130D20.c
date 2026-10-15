// Reference algorithm: src/hand/func_0012E6A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00167960(void *,float);
void func_00169E28(void *p); void func_00130D20(char *p) { func_00169E28(p); if(*(float *)(*(char **)(p + 0x20) + 0x11C) != 0.0f) func_00167960(*(void **)p, *(float *)(*(char **)(p + 0x20) + 0x11C)); }

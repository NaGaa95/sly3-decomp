// Reference algorithm: src/hand/func_001F3868.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00252E40(void *,int);
void func_00238970(void *p);
void func_001D9340(char *p) { func_00238970(p); *(float *)(p + 0x38) = -1.0f; func_00252E40(*(void **)(p + 0x10), 0x3F); }

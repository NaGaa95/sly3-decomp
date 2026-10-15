// Reference algorithm: src/hand/func_0013CFD8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00252E40(void *,int);
void func_00238970(void *p); void func_0015F7A8(char *p) { func_00238970(p); *(int *)(p + 0x30) = -1; *(int *)(p + 0x38) = -1; *(int *)(p + 0x40) = -1; *(int *)(p + 0x70) = -1; func_00252E40(*(void **)(p + 0x10), 0x42); }

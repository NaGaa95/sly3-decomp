// Reference algorithm: src/hand/func_0015CD68.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00252E40(void *,int);
void func_00238970(void *p);
void func_001977F8(char *p) { func_00238970(p); *(int *)(p + 0x4C) = -1; *(int *)(p + 0x50) = -1; *(int *)(p + 0x54) = 0; func_00252E40(*(void **)(p + 0x10), 0x35); }

// Reference algorithm: src/hand/func_0014A200.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00252E40(void *,int);
void func_00238970(void *p); void func_001F5AE0(char *p) { func_00238970(p); func_00252E40(*(void **)(p + 0x10), 0x41); *(int *)(p + 0x30) = -1; *(int *)(p + 0x3C) = *(int *)(*(char **)(p + 0x10) + 0x164); }

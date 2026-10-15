// Reference algorithm: src/hand/func_00203758.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001BE4F8(void *,void *); void func_001BDA30(char *p,void *owner) { *(void **)p = owner; *(int *)(p + 4) = -1; *(int *)(p + 0x18) = -1; func_001BE4F8(p + 0x1C, p); }

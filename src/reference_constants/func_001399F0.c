// Reference algorithm: src/hand/func_00132B78.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_0011B0C0(void *,void *); void func_0011AF90(void *,void *); void func_001399F0(char *p) { void *list = *(char **)(p + 0x10) + 0x10EC; if(!func_0011B0C0(list, p)) func_0011AF90(list, p); }

// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001F43C8(void *); void func_001F43D0(void *,int); void func_001F43F8(char *p,int value) { *(int *)(p + 0x170) = value; func_001F43D0(p, func_001F43C8(p)); }

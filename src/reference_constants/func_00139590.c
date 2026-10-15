// Reference algorithm: src/hand/func_0020CE40.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; void func_0013CD10(void *,void *); void func_00139590(char *p) { *(int *)(p + 0x130) = 0; func_0013CD10(D_00475480, p); }

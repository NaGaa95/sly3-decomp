// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; void func_001CAC30(void *,int); void func_001F4B00(void *,int,void *); void func_001CAF30(char *p,int value) { *(int *)(p + 0x1F0) = value; func_001CAC30(p, 1); func_001F4B00(D_00475480, 0, p); }

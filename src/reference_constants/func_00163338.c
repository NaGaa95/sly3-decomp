// Reference algorithm: src/hand/func_00179598.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; void *func_0017E1B8(void *,int,int,void *); void func_001F4670(void *,int);
void func_001F3BF8(void *p); void func_00163338(char *p) { func_001F3BF8(p); *(void **)(p + 0x194) = func_0017E1B8(D_00475480, 0x405, 0x416, 0); func_001F4670(p, 1); }

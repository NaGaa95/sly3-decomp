// Reference algorithm: src/hand/func_00210B28.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; void func_0013BAC8(void *,int); void func_0012BDD8(void *,int); void *func_00125DC0(void *p,void *unused,int *source) { func_0013BAC8(D_00475480, source[1]); func_0012BDD8(p, 0x22); return p; }

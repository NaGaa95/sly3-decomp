// Reference algorithm: src/hand/func_001BC050.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036E260[]; void func_00194280(void *,void *,void *); void func_00194480(void *,int,void *); void func_001944E8(void *a,void *b,void *p) { func_00194280(a, b, p); func_00194480(p, 2, D_0036E260); }

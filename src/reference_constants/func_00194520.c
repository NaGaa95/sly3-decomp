// Reference algorithm: src/hand/func_001BC050.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036E280[]; void func_00194308(void *,void *,void *); void func_00194480(void *,int,void *); void func_00194520(void *a,void *b,void *p) { func_00194308(a, b, p); func_00194480(p, 2, D_0036E280); }

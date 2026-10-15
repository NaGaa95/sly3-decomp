// Reference algorithm: src/hand/func_001AE4F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; int func_00165B48(void *,void *); int func_00165DC8(void *p) { return func_00165B48(D_00475480, p) < 0; }

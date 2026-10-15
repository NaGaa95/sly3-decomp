// Reference algorithm: src/hand/func_0020CE40.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00479BC8[]; void func_0011AF60(void *,void *); void func_001C0370(void **p,void *owner) { *p = owner; func_0011AF60(D_00479BC8, p); }

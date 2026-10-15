// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; void func_0013CD10(void *,void *);
void func_0016C9C0(void *p);
void func_0016D2E8(char *p) { func_0016C9C0(p); func_0013CD10(D_00475480, *(void **)(p + 0x10)); }

// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD8]; int fe8; };
extern char D_00475480[];
void func_0023C580(struct S *);
void func_0013CD10(void *, struct S *);
void func_00139260(struct S *p) { func_0023C580(p); if (p->fe8) func_0013CD10(D_00475480, p); }

// Reference algorithm: src/hand/func_001FB018.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x5A]; short c; };
void func_00245320(struct S *, int, int);
void func_00244C28(struct S *p) { if (++p->c == 1) func_00245320(p, 6, 2); }

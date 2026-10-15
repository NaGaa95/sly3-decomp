// Reference algorithm: src/hand/func_0020B4A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x3C]; int fl; };
void func_001C7340(struct S *p);
void func_001C9118(struct S *p, int n);
void func_00257260(struct S *p) {
    int v;
    func_001C7340(p);
    v = p->fl;
    if ((v ^ 1) & 1) *(int *)v |= 2; else p->fl = v | 2;
    func_001C9118(p, 1);
}

// Reference algorithm: src/hand/func_001DCE90.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char p0[0x58]; int c; char p1[0x118-0x4C]; int i; };
void func_0021EDC0(struct S *p);
static inline int Clamp(int n, int lo, int hi) {
    if (n < lo) return lo;
    if (n > hi) return hi;
    return n;
}
void func_002210C0(struct S *p, int i) {
    int c = p->c;
    int n;
    if (c == 0) n = -1;
    else n = Clamp(i, 0, c - 1);
    p->i = n;
    func_0021EDC0(p);
}

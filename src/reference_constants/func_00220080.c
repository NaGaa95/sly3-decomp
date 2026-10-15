// Reference algorithm: src/hand/func_001DBBA0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern int D_0034939C;
extern int D_0046FD40;
struct S { char p0[0x58]; int n48; char p1[0x278-0x5C]; int n250; };
int func_00220080(struct S *p) {
    int n = p->n250 + D_0034939C;
    if (D_0046FD40) {
        n -= (p->n250 > 0);
        n -= (n < p->n48);
    }
    return n;
}

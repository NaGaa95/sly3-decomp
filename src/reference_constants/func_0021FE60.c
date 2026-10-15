// Reference algorithm: src/hand/func_001DD780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x48]; int n58; char p1[8]; int n64; };
struct S { char pad[0x34]; struct O *po; };
int func_0021FE60(struct S *p) {
    struct O *po = p->po;
    if (!po) return 0;
    if (po->n58 != 2) return 0;
    return po->n64 == 2;
}

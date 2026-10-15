// Reference algorithm: src/hand/func_002026F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -O2 -G0
struct G;
extern struct G D_00474FF0;
struct S { char pad[0x48]; int oid; };
int func_00248858(struct G *p, int oid);
int func_0018C170(struct S *p) { if (p->oid == -1) return 1; return func_00248858(&D_00474FF0, p->oid) == 0; }

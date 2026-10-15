// Sly 2 reference: src/hand/func_00202730.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct G;
extern struct G D_00475480;
struct S { char pad[0xBC]; int oid; };
const unsigned short *func_00150630(struct G *p, int oid);
const unsigned short *func_0024C6A0(struct S *p) { if (p->oid == -1) return 0; return func_00150630(&D_00475480, p->oid); }

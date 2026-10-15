// Reference algorithm: src/hand/func_001DFAD8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct DL { void *a, *b; int ib; };
struct S { char pad[0x1B4]; struct DL dl; char unknown_tail[0x18]; int n58; };
void func_0022D708(struct S *p);
void func_0011AF38(struct DL *pdl, int ib);
void func_001E6200(struct S *p) {
    func_0022D708(p);
    p->n58 = -1;
    func_0011AF38(&p->dl, 0x1C0);
}

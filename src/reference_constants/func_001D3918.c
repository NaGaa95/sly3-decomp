// Reference algorithm: src/hand/func_001AF490.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x38]; int x24; char pad2[0x1C0]; int x1e8; int x1ec; };
void func_001D2ED0(struct S *p, int n);
void func_001D3918(struct S *p)
{
    if (p->x1e8 == 7) {
        func_001D2ED0(p, 3);
        p->x1ec = p->x24 - 1;
    }
}

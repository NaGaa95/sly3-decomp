// Reference algorithm: src/hand/func_001AF608.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x38]; int x24; char pad2[0x1C0]; int x1e8; int x1ec; };
void func_001D2ED0(struct S *p, int n);
int func_001D4658(struct S *p);
void func_001D3A90(struct S *p)
{
    if (p->x1e8 == 7) {
        func_001D2ED0(p, 2);
        if (func_001D4658(p)) p->x1ec = p->x24 = p->x24 - 1;
    }
}

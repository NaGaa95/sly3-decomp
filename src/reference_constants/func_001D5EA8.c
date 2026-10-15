// Reference algorithm: src/hand/func_001B10D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct M { char pad[0x14]; int n; };
struct S { char pad[0x184]; int n1a4; char pad2[0x1A4 - 0x188]; struct M *pm; };
void func_0013BEC0(struct S *p, int msg, struct M *pm);
void func_001D6110(struct S *p, int n);
void func_001D5EA8(struct S *p, int msg, struct M *pm)
{
    func_0013BEC0(p, msg, pm);
    if (msg == 4 && pm == p->pm && pm->n == p->n1a4) func_001D6110(p, 4);
}

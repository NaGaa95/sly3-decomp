// Reference algorithm: src/hand/func_0018DE80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x19E0]; int n; };
void func_00155D60(struct S *p, int *pf);
void func_001AFB10(struct S *p, int *pf)
{
    func_00155D60(p, pf);
    switch (p->n) {
    case 0: case 1: case 2: case 6: case 10: case 23:
        *pf = 1;
    }
}

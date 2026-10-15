// Reference algorithm: src/hand/func_001E5DB8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x16C]; int n; };
void func_0028FE20(struct S *p);
void func_0022F450(struct S *p, int n);
void func_0022D740(struct S *p)
{
    func_0028FE20(p);
    if (p->n) {
        p->n = 0;
        func_0022F450(p, 0);
    }
}

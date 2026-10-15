// Reference algorithm: src/hand/func_001B9C00.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1140]; void *p1034; char pad1[0x1674 - 0x1144]; void *p1530; int n1534; };
void func_001DE690(struct S *p, int n);
void func_00239FE0(void *p, int n);
void func_00239CE8(void *p, int n);
void func_001E2848(struct S *p, void *pv, int n, int m, int f)
{
    p->p1530 = pv;
    p->n1534 = m;
    func_001DE690(p, 6);
    if (n == -1)
        return;
    if (p->p1530) {
        if (f)
            func_00239FE0(p->p1530, n);
        else
            func_00239CE8(p->p1530, n);
    }
    if (f)
        func_00239FE0(p->p1034, n);
    else
        func_00239CE8(p->p1034, n);
}

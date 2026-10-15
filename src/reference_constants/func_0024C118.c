// Reference algorithm: src/hand/func_002021F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern int D_00349370[];
struct S { char pad[0x74]; int n; int a[(0xAC - 0x78) / 4]; int hAC; };
int func_0024D6B0(int x);
void func_00262540(int h, int id, int v);
void func_0024C118(struct S *p)
{
    int i;
    for (i = 0; i < p->n; i++) {
        int v;
        int a = p->a[i];
        v = D_00349370[i];
        if (func_0024D6B0(a))
            func_00262540(p->hAC, 0x3C1, v);
        else
            func_00262540(p->hAC, 0x3C2, v);
    }
}

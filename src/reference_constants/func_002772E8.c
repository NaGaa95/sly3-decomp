// Reference algorithm: src/hand/func_002242E0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x130]; int k; };
int func_0023E178(struct S *p, void *q);
int func_0013B500(void *q, int a);
int func_0013CD00(int v, int a);
int func_002772E8(struct S *p, void *q)
{
    int v = func_0023E178(p, q);
    int k = p->k;
    if (k == 0 || k == 4) { if (func_0013B500(q, 0x33)) v = func_0013CD00(v, 1); }
    return v;
}

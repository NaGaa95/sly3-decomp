// Reference algorithm: src/hand/func_00226310.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0x38]; int k; };
struct S { char pad[0x1D0]; struct T *t; };
int func_0023E178(struct S *p, struct T *q);
int func_0013CD00(int v, int a);
int func_0027D5A8(struct S *p, struct T *q)
{
    int v = func_0023E178(p, q);
    if (p->t && q->k == p->t->k) v = func_0013CD00(v, 1);
    return v;
}

// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct T { int n; };
struct S { char pad[0x60]; int n60; };
int func_00237348(struct S *p, struct T *t);
int func_00237BE0(struct S *p, struct T *t)
{
    int f = 0;
    if (func_00237348(p, t) || t->n == p->n60) f = 1;
    return f;
}

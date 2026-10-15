// Reference algorithm: src/hand/func_0014AD70.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int k; int a, b; };
struct Q { char pad[0x48]; struct E *ae; };
struct P { char pad[0x38]; struct Q *q; int i; int c; };
void func_0015F050(struct P *p, int n);
void func_0015EF88(struct P *p)
{
    int k;
    if (p->i < p->c) {
        p->i++;
        k = p->q->ae[p->i].k;
    } else {
        k = p->q->ae[p->i].k;
        p->i--;
    }
    switch (k) {
    case 0:
        func_0015F050(p, 1);
        break;
    case 1:
        func_0015F050(p, 2);
        break;
    }
}

// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct C { unsigned char a[4]; };
struct S { int k; struct C c; int z; };
void func_0027EB50(struct C *pc, int a);
void func_0027ED18(struct S *p)
{
    struct C c;
    p->k = -1;
    func_0027EB50(&c, -1);
    p->c = c;
    p->z = 0;
}

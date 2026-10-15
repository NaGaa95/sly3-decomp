// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x18]; int c; char pad2[0xE0]; int *a; int *ai; };
int *func_00246E98(struct S *p, int n)
{
    int i;
    if (n < 0 || n >= p->c) return 0;
    i = p->ai[n];
    if (i < 0) return 0;
    return &p->a[i];
}

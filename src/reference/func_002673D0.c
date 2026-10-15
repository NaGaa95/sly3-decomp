// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
struct S { char pad[0x28]; int f; };
void func_002673F8(struct S *p, int a, int b);
void func_002673D0(struct S *p)
{
    if (p->f)
        func_002673F8(p, 0, 0);
}

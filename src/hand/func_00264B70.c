// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct RGBA { unsigned char r, g, b, a; };
struct S { char pad[0x14]; struct RGBA c1; struct RGBA c0; };
void func_00264F10(struct S *p);
void func_00264B70(struct S *p, struct RGBA *pc)
{
    p->c0 = *pc;
    p->c1 = p->c0;
    func_00264F10(p);
}

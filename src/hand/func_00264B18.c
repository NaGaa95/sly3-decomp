// Actual nullable sixteen-bit text pointer and sixteen-bit cursor semantics.
// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct RGBA { unsigned char r, g, b, a; };
struct S { const unsigned short *x0; const unsigned short *x4; void *x8; void *xc; void *x10; struct RGBA c1; struct RGBA c0; unsigned int x1c; };
void func_00264F10(struct S *p);
void func_00264B18(struct S *p, const unsigned short *a)
{
    if (a)
        p->x0 = a;
    p->x4 = p->x0;
    p->x8 = p->xc;
    p->c1 = p->c0;
    p->x1c = 0x80000000;
    ((unsigned char *)&p->x1c)[3] = p->c1.a;
    func_00264F10(p);
}

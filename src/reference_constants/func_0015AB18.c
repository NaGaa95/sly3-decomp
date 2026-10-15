// Reference algorithm: src/hand/func_00147C20.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct P { char pad[0x140]; char asega[4]; int n164, n168, n16C, n170; };
void *func_0017E1B8(void *p, int k, int oid, void *q);
void func_00137588(void *aseg, void *alo, float t, float s, int n, void *pp);
void func_0015A038(struct P *p, int n);
void func_0015AB18(struct P *p, int oid, int n)
{
    char *aseg;
    p->n170 = n;
    p->n16C = 1;
    p->n168 = 1;
    p->n164 = 1;
    aseg = func_0017E1B8(D_00475480, 1, oid, p);
    if (aseg) {
        unsigned int v = *(unsigned int *)(aseg + 0x3C);
        if ((v ^ 1) & 1) *(int *)v |= 0x200;
        else *(unsigned int *)(aseg + 0x3C) = v | 0x200;
        func_00137588(aseg, p, 0.0f, 1.0f, 4, p->asega);
        func_0015A038(p, 0);
    }
}

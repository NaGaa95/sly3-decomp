// Reference algorithm: src/hand/func_001C4228.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; int (*pfn)(void *, int, int, int, void **, int); };
struct O { int a[3]; struct VTE *vt; };
void func_001F48A0(struct O *p, int a, int b)
{
    void *apv[2];
    int n0, n1;
    /*B*/n0 = a; n1 = b; apv[0] = &n0; apv[1] = &n1;/*E*/
    { struct VTE *e = &p->vt[3]; e->pfn((char *)p + e->d, 0xF, 0, 2, apv, 0); }
}

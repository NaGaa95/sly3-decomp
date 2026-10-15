// Reference algorithm: src/hand/func_001A6CA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O {
    char pad[0x10];
    struct O *pParent;
    void *pv14;
    char pad2[0x10];
    unsigned long b0 : 48;
    long n52 : 4;
    unsigned int b56 : 4;
    unsigned int f60 : 1;
};
extern char D_00475480[];
void func_0015ADA0(void *, void *);
void func_001C9118(struct O *p, int n)
{
    if (n != p->n52) {
        p->n52 = n;
        if (!p->pParent && p->f60 != 0)
            func_0015ADA0(D_00475480, p->pv14);
    }
}

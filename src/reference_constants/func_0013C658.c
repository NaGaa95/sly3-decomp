// Reference algorithm: src/hand/func_00133D08.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VT { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VT *pvt; };
struct B { float min[4]; float max[4]; char pad[0x60 - 0x20]; struct O *po; };
int func_0013CD00(int a, int b);
static __inline__ int Call(struct O *po, struct O *poOther)
{
    return ((int (*)(void *, struct O *))po->pvt[65].pfn)((char *)po + po->pvt[65].d, poOther);
}
int func_0013C658(void *unused, struct B *pa, struct B *pb)
{
    int n1, n2, r;
    if (pa->min[0] >= pb->max[0] || pa->min[1] >= pb->max[1] || pa->min[2] >= pb->max[2] ||
        pb->min[0] >= pa->max[0] || pb->min[1] >= pa->max[1] || pb->min[2] >= pa->max[2])
        return 0;
    n1 = Call(pa->po, pb->po);
    n2 = Call(pb->po, pa->po);
    r = func_0013CD00(n1, n2);
    return r != 1 && r != 3;
}

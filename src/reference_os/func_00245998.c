// Sly 2 reference: src/hand/func_001FBB30.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct A { char pad[0xC]; struct VTE *vt; };
void func_00244CA8(struct A *p, float g);
void func_00245320(struct A *p, int a, int b);
void func_00245998(int f, long l)
{
    struct A *p = (struct A *)l;
    if (!f)
        func_00244CA8(p, 0.0f);
    else
        func_00245320(p, 0x400, 0x400);
    p->vt[2].pfn((char *)p + p->vt[2].d);
}

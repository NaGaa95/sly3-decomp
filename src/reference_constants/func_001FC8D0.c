// Reference algorithm: src/hand/func_0015C628.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
void func_001FC8D0(struct O *o, int x)
{
    struct VTE *e = &o->vt[31];
    e->pfn((char *)o + e->d, x);
}

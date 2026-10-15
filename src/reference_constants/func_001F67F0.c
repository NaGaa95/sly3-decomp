// Reference algorithm: src/hand/func_001C7EA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { int a[3]; struct VTE *vt; };
void func_001FCB20(struct O *p);
void func_001F67F0(struct O *p)
{
    func_001FCB20(p);
    { struct VTE *e = &p->vt[80]; e->pfn((char *)p + e->d, -1); }
}

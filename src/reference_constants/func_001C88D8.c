// Reference algorithm: src/hand/func_001A6450.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void *pfn; };
struct O { int x0, x4, x8; struct VTE *vt; };
void func_001C88D8(struct O *o, void *arg)
{
    struct O **list;
    int n, i;
    struct VTE *e = &o->vt[0x108 / 8];
    n = ((int (*)(void *, struct O ***))e->pfn)((char *)o + e->d, &list);
    for (i = 0; i < n; i++) {
        struct O *p = list[i];
        struct VTE *f = &p->vt[0x150 / 8];
        ((void (*)(void *, void *))f->pfn)((char *)p + f->d, arg);
    }
}

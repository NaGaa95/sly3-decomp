// Reference algorithm: src/hand/func_001371C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; char pad2[0x112C]; int f1030; };
struct S { char unknown_prefix[0x10]; struct O *po; };
int func_00138AC8(int);
void func_001408B0(struct S *p) {
    if (func_00138AC8(p->po->f1030)) {
        struct O *po = p->po; struct VTE *vt = po->vt;
        ((void (*)(void *, int))vt[99].pfn)((char *)po + vt[99].d, 0);
    }
}

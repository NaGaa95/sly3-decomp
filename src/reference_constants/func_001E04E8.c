// Reference algorithm: src/hand/func_001B7BA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
#include "activation_selector_api.h"
typedef int qword __attribute__((mode(TI)));
struct VE { short d; short pad; void (*pfn)(); };
struct X { char pad[0xC]; struct VE *vt; };
struct O { char pad[0xC]; struct VE *vt; char pad1[0x190 - 0x10]; struct X *x180; };
struct P { char pad[0x1520]; int x13D0; char pad1[0x13F0 - 0x13D4]; struct O *x13F0; char pad2[0x158C - 0x1544]; int x1450; char pad3[0x1674 - 0x1590]; void *x1530; };
extern qword D_00324690, D_00317560;
void func_001E0660(struct P *p);
int func_0013B500(struct X *x, int n);
void func_00255960(struct X *x);
void func_00241150(struct X *x, int n);
qword func_001C94E8(struct P *p, int n, qword q);
void func_001E04E8(struct P *p)
{
    struct O *o;
    struct X *x;
    if (p->x13D0 == 6) {
        if (p->x1530) func_00239CE8(p->x1530, 0x1F8);
        return;
    }
    o = p->x13F0;
    if (!o) return;
    if (p->x13D0 == 4 && p->x1450 == 0) {
        ((void (*)())o->vt[3].pfn)((char *)o + o->vt[3].d, 6, 0, 0, 0, 0);
        p->x13F0 = 0;
        return;
    }
    func_001E0660(p);
    x = p->x13F0->x180;
    if (func_0013B500(x, 0x3A)) func_00255960(x);
    else func_00241150(x, 1);
    switch (p->x13D0) {
    case 5: {
        struct VE *e = &x->vt[40];
        ((void (*)(void *, qword))e->pfn)((char *)x + e->d, func_001C94E8(p, 0, D_00324690));
        break;
    }
    case 2: case 4: case 7: case 8:
        ((void (*)(void *, qword))x->vt[40].pfn)((char *)x + x->vt[40].d, D_00317560);
        break;
    case 3: case 6:
        break;
    }
    p->x13F0 = 0;
}

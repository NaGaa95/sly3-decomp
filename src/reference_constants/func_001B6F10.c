#include "actor_resource_lookup_api.h"
// Reference algorithm: src/hand/func_001956D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE {
    short d;
    short pad;
    void (*pfn)();
};
struct O {
    int a, b, c;
    struct VTE *vt;
};
struct E {
    int pad[8];
    qword q20;
};
extern qword D_00317560;
extern char D_00317490[];
#include "owner_parent_link.h"
void func_00241338(struct O *, float);
struct O *func_001B6F10(void *p, int id, struct E *pe) {
    struct O *po;
    if (!id) return 0;
    po = func_001FBE30((void *)id, 0);
    if (po) {
        func_001C7A00(po, 0, 0);
        {
            struct VTE *e = &po->vt[9];
            ((void (*)(void *))e->pfn)((char *)po + e->d);
        }
        func_00241338(po, 0.25f);
        {
            struct VTE *e = &po->vt[34];
            ((void (*)(void *, qword))e->pfn)((char *)po + e->d, pe->q20);
        }
        {
            struct VTE *e = &po->vt[35];
            ((void (*)(void *, void *))e->pfn)((char *)po + e->d, D_00317490);
        }
        {
            struct VTE *e = &po->vt[40];
            ((void (*)(void *, qword))e->pfn)((char *)po + e->d, D_00317560);
        }
        {
            struct VTE *e = &po->vt[41];
            ((void (*)(void *, qword))e->pfn)((char *)po + e->d, D_00317560);
        }
    }
    return po;
}

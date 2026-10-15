// Copy the complete aligned value into the cached resource, allocating it on first use.
// SLY3_CFLAGS: -Os -G0
#include "matrix_xy_resource_api.h"
struct VE {
    short d;
    short pad;
    struct MatrixXYValue *(*pf)(void *, int, int);
};
struct A {
    struct VE *vt;
};
struct S {
    char pad[0xB4];
    struct A *pa;
    char pad2[0x34];
    struct MatrixXYValue *pm;
};
void func_00262848(void *receiver, const struct MatrixXYValue *src) {
    struct S *p = (struct S *)receiver;
    if (!p->pm) {
        struct A *a = p->pa;
        p->pm = a->vt[1].pf((char *)a + a->vt[1].d, 0x20, 0x29);
    }
    *p->pm = *src;
}

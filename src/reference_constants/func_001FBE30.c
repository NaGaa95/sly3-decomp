#include "actor_resource_lookup_api.h"
// Reference algorithm: src/hand/func_001CB250.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T {
    int n;
    void **ap;
};
struct S {
    char pad[0xD0];
    struct T *pt;
};
void *func_001FBB08(struct S *p, int n);
int func_001FB5D8(struct S *p, void *q);
void *func_001FBE30(void *resource, int f) {
    /*B*/struct S *p=(struct S *)resource;
    void *q;
    if (p->pt->n != 1) return 0;
    q = func_001FBB08(p, f ? 1 : 2);
    if (!q) return 0;
    return p->pt->ap[func_001FB5D8(p, q)];
    /*E*/
}

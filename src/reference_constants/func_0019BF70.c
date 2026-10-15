// Reference algorithm: src/hand/func_0017F770.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
#include "activation_selector_api.h"
typedef int qword __attribute__((mode(TI)));
extern qword D_00317560;
struct G;
extern struct G D_00475480;
struct E { int a; int b; int c; int d; void *e; void *f; };
struct S { char pad[0x28C]; int c; struct E ae[1]; };
int func_0023DDA0(struct S *p, int a, int b);
void *func_0017E1B8(struct G *pg, int k, int b, struct S *p);
int func_00130078(struct S *p, int c, int a, int b, int d, qword q);
void func_0019BF70(struct S *p) {
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        pe->c = func_0023DDA0(p, pe->a, 6);
        pe->e = func_0017E1B8(&D_00475480, 4, pe->b, p);
        if (pe->c) pe->d = func_00130078(p, pe->c, 0, 8, 2, D_00317560);
        if (pe->e) pe->f = func_002399C8(pe->e, p, -1, 0);
    }
}

#include "heap_frame_api.h"
// Sly 2 reference: src/hand/func_0020F640.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
extern int D_0047A48C;
extern int D_0047A484;
struct L {
    int a[4];
};
struct M {
    int a;
    int b;
    int c[2];
};
void func_00118DC0(void *q, int n);
void *func_001D25B0(struct M *pm);
void func_00118DA0(void *q, int a, void *x);
void func_00233AE0(void *x);
void func_00196E08(void *p);
void func_00118DF0(void *q, int a);
void func_00196F00(void *p);
void func_0025C9A0(void *p, void *q) {
    func_00118DC0(q, 0x10);
    if (D_0047A48C) {
        struct L l;
        struct M m;
        void *x;
        func_001D2770(&l);
        {
            struct M *pm = &m;
            pm->a = D_0047A484;
            pm->b = 0x10;
            x = func_001D25B0(pm);
        }
        func_00118DA0(q, D_0047A484, x);
        func_00233AE0(x);
        func_00196E08(p);
        func_001D2798(&l, 2);
    }
    else {
        func_00118DF0(q, D_0047A484);
        func_00196F00(p);
    }
}

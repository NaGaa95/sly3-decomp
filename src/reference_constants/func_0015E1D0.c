#include "heap_frame_api.h"
// Reference algorithm: src/hand/func_0014A008.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S {
    int a, b;
};
struct F {
    int a[4];
};
struct P {
    char pad[0x44];
    int n54;
    int n58;
};
int func_001D2670(struct S *s);
void func_001C7D98(struct P *p, int a);
int func_001D24D0(struct S *s, int n);
static inline void InitS(struct S *ps, int a, int b) {
    ps->a = a * 0xC;
    ps->b = b;
}
void func_0015E1D0(struct P *p, int a) {
    struct F f;
    struct S s;
    func_001D2770(&f);
    InitS(&s, 0x100, 0x10);
    p->n58 = func_001D2670(&s);
    func_001C7D98(p, a);
    InitS(&s, p->n54, 0x10);
    p->n58 = func_001D24D0(&s, p->n58);
    func_001D2798(&f, 2);
}

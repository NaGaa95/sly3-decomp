#include "heap_frame_api.h"
// Allocate 64 initial records of 0x170 bytes inside an allocation frame, initialize the object, and resize storage to its actual count.
// Reference algorithm: src/hand/func_0014A008.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S {
    int a, b;
};
struct F {
    int a[4];
};
struct P {
    char pad[0x178];
    int n54;
    int n58;
};
int func_001D2670(struct S *s);
void func_0023C0B8(struct P *p, int a);
int func_001D24D0(struct S *s, int n);
static inline void InitS(struct S *ps, int a, int b) {
    ps->a = a * 0x170;
    ps->b = b;
}
void func_00223918(struct P *p, int a) {
    struct F f;
    struct S s;
    func_001D2770(&f);
    InitS(&s, 0x40, 0x10);
    p->n58 = func_001D2670(&s);
    func_0023C0B8(p, a);
    InitS(&s, p->n54, 0x10);
    p->n58 = func_001D24D0(&s, p->n58);
    func_001D2798(&f, 2);
}

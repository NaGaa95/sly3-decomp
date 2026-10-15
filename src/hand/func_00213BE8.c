#include "heap_frame_api.h"
// Create a temporary allocation frame, initialize object state, and resize its descriptor storage to the final count.
// Reference algorithm: src/hand/func_0013BE58.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R {
    int cb;
    int cbAlign;
};
struct C {
    int a[4];
};
struct S {
    char pad[0x1D4];
    void *pv;
    int c;
};
void *func_001D2670(struct R *);
void func_001F3BC8(struct S *, void *);
void func_00215198(struct S *);
void *func_001D24D0(struct R *, void *);
static inline struct R *SetReq(struct R *pr, int cb, int cbAlign) {
    pr->cb = cb;
    pr->cbAlign = cbAlign;
    return pr;
}
void func_00213BE8(struct S *p, void *a) {
    struct C ctx;
    struct R req;
    func_001D2770(&ctx);
    p->pv = func_001D2670(SetReq(&req, 0xB0, 0x10));
    func_001F3BC8(p, a);
    func_00215198(p);
    p->pv = func_001D24D0(SetReq(&req, p->c * 0x2c, 0x10), p->pv);
    func_001D2798(&ctx, 2);
}

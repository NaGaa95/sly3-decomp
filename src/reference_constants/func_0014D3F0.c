#include "heap_frame_api.h"
// Reference algorithm: src/hand/func_0013BE58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct R {
    int cb;
    int cbAlign;
};
struct C {
    int a[4];
};
struct S {
    char pad[0x130];
    int c;
    void *pv;
};
void *func_001D2670(struct R *);
void func_0023C0B8(struct S *, void *);
void func_0014DB68(struct S *);
void *func_001D24D0(struct R *, void *);
static inline struct R *SetReq(struct R *pr, int cb, int cbAlign) {
    pr->cb = cb;
    pr->cbAlign = cbAlign;
    return pr;
}
void func_0014D3F0(struct S *p, void *a) {
    struct C ctx;
    struct R req;
    func_001D2770(&ctx);
    p->pv = func_001D2670(SetReq(&req, 0x580, 0x10));
    func_0023C0B8(p, a);
    func_0014DB68(p);
    p->pv = func_001D24D0(SetReq(&req, p->c * 0x2c, 0x10), p->pv);
    func_001D2798(&ctx, 2);
}

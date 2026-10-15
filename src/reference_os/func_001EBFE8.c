#include "heap_frame_api.h"
// Sly 2 reference: src/hand/func_001BFC18.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct CTX {
    int a[4];
};
struct REQ {
    int cb;
    int align;
};
void *func_001D25B0(struct REQ *r);
void func_001D2898(void *dst, void *src, int cb);
int func_001EBCD0(void *ctx, qword a, qword b, int n);
static __inline__ void *PvAllocReq(struct REQ *preq, int cb, int nKind) {
    preq->cb = cb;
    preq->align = nKind;
    return func_001D25B0(preq);
}
void func_001EBFE8(void *ctx, int *pc, qword **ap) {
    struct CTX c;
    struct REQ req;
    qword **tmp, **prev, **cur, **next, **end;
    int n, k;
    func_001D2770(&c);
    n = *pc;
    end = ap + n;
    tmp = PvAllocReq(&req, n * 4, 0x10);
    tmp[0] = ap[0];
    k = 1;
    prev = ap;
    cur = ap + 1;
    next = ap + 2;
    while (next < end) {
        if (func_001EBCD0(ctx, **prev, **next, 0)) {
            tmp[k] = *cur;
            prev = cur;
            cur = next++;
            k++;
        }
        else {
            cur = next++;
        }
    }
    tmp[k] = ap[n - 1];
    k++;
    if (k < n && k >= 3) func_001EBFE8(ctx, &k, tmp);
    func_001D2898(ap, tmp, k * 4);
    *pc = k;
    func_001D2798(&c, 2);
}

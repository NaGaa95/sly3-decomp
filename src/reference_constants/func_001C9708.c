// Reference algorithm: src/hand/func_001A71B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
struct VTE { short d; short pad; void *(*pfn)(void *); };
struct O { int x0, x4, x8; struct VTE *vt; };
void func_0011D768(M4 *out, void *in);
void func_0011D558(M4 *out, void *a, M4 *b);
M4 func_001C9708(struct O *o1, struct O *o2, M4 *m)
{
    M4 t;
    M4 r;
    M4 inv;
    struct VTE *e;
    if (o1) {
        e = &o1->vt[0x120 / 8];
        func_0011D558(&r, e->pfn((char *)o1 + e->d), m);
        t = r;
    } else {
        t = *m;
    }
    if (o2) {
        M4 *pinv = &inv;
        M4 *pr = &r;
        e = &o2->vt[0x120 / 8];
        func_0011D768(pinv, e->pfn((char *)o2 + e->d));
        func_0011D558(pr, pinv, &t);
        t = r;
    }
    return t;
}

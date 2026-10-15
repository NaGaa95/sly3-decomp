// Sly 2 reference: src/hand/func_00204ED8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct { short d; short pad; void *pfn; } VTE;
extern qword D_00317560;
struct O { VTE *vt; };
struct X { int a; struct O *po; };
struct Q { char pad[0x14]; int n14; char pad2[0x40 - 0x18]; float g40; };
int func_00138AC8(struct Q *q);
struct X *func_00136EE0(int n, void *p, int a, int b);
qword func_0024F318(void *p, struct Q *q, float g)
{
    qword r = D_00317560;
    if (q && !func_00138AC8(q)) {
        struct X *x = func_00136EE0(q->n14, p, 6, 1);
        if (x) {
            struct O *o = x->po;
            ((void (*)(void *, int, qword *, float, float))o->vt[3].pfn)((char *)o + o->vt[3].d, 0, &r, g, q->g40);
        }
    }
    return r;
}

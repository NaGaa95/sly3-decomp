// Reference algorithm: src/hand/func_0017ABC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct VTE { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VTE *vt; };
struct R { int n0; int a[11]; };
struct U { char pad[0x1C]; float g1C; };
struct W { char pad[0xA0]; int nA0; };
struct T { char pad[0x48]; struct W *p58; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x48]; struct O *p5C; int n60; struct U *p64; };
void func_0016D9F0(struct S *p, struct R *r, qword *a, qword *b);
qword func_0028E910(int a, int b, qword q);
qword func_0028E990(int a, int b, qword q);
void func_001305C8(struct U *u, qword a, qword b);
void func_0016DB68(struct S *p) {
    struct R r;
    qword q30, q40;
    struct W *w;
    qword a;
    if (!p->n60) return;
    { struct O *o = p->p5C; struct VTE *e = &o->vt[0x6D]; ((void (*)(void *, struct R *, float))e->pfn)((char *)o + e->d, &r, p->p64->g1C - D_0036BB98.t); }
    if (!r.n0) { p->n60 = 0; return; }
    w = p->pt->p58;
    func_0016D9F0(p, &r, &q30, &q40);
    a = func_0028E910(0, w->nA0, q30);
    func_001305C8(p->p64, a, func_0028E990(0, w->nA0, q40));
}

// Reference algorithm: src/hand/func_0019E950.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(void *, int, int, qword, qword, qword); };
struct O { int a, b, c; struct VTE *vt; };
struct S { struct O *o; int pad[2]; int c; float g; int pad2[7]; qword q30; };
void func_0022E330(int, qword *, qword *, float);
qword func_001C9428(struct O *, int, qword);
typedef union { qword q; float f[4]; } V;
void func_001BF990(struct S *p) {
    V a, b, u;
    func_0022E330(p->c, &a.q, &b.q, p->g);
    u.q = func_001C9428(p->o, 0, p->q30);
    { struct O *o = p->o; struct VTE *e = &o->vt[93]; e->pfn((char *)o + e->d, 7, p->c, a.q, b.q, u.q); }
}

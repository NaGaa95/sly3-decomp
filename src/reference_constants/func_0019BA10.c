// Reference algorithm: src/hand/func_0017F4C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct R { int n0; void *p4; void *p8; int nC; };
struct S { char pad[0x19C]; void *p194; int a198[1]; };
void func_0023AC58(void *p);
void func_00137628(void *pp);
void func_00137588(void *paseg, struct S *p, float t, float svt, int grf, void *pp);
void func_0023AAE8(void *a, struct S *p, int b, int c, void *d);
void func_0019BA10(struct S *p, struct R *r) {
    func_0023AC58(p->a198);
    func_00137628(&p->p194);
    if (r) {
        func_00137588(r->p4, p, 0.0f, 1.0f, r->nC, &p->p194);
        func_0023AAE8(r->p8, p, -1, r->nC, p->a198);
    }
}

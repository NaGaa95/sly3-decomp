// Reference algorithm: src/hand/func_001D7780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { int tagk; int tag; } CRef;
struct S { char p0[0x230]; int a220; int a224; };
void func_0024B330(CRef *pref, void *pv, int a, int b, int *pa, int *pb);
void func_0012BC20(CRef *pref);
void func_00213728(struct S *p, int n);
void func_002136D8(struct S *p, void *pv) {
    CRef ref;
    func_0024B330(&ref, pv, 6, 6, &p->a220, &p->a224);
    func_0012BC20(&ref);
    func_00213728(p, 0);
}

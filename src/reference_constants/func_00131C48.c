// Reference algorithm: src/hand/func_00175090.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T {
    char pad[0x48];
    void *n58;
    void *n5C;
};
struct S {
    char pad[0x10];
    struct T *pt;
    char pad2[0x24];
    int n38;
};
void func_00131770(struct S *p);
void func_0028F068(struct T *t, void *a, int b);
void func_00131C48(struct S *p) {
    func_00131770(p);
    func_0028F068(p->pt, p->pt->n58, 2);
    if (!p->n38) func_0028F068(p->pt, p->pt->n5C, 2);
}

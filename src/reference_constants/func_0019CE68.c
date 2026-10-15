// Reference algorithm: src/hand/func_001805C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S {
    char pad[0x48];
    void *a;
    void *b;
    char p2[0x1B4];
    int x1d8;
    char p3[0x48];
    char x220[4];
};
void func_001F3BF8(struct S *p);
int func_00231138(int a, int b);
void func_0028F068(struct S *p, void *a, int b);
void func_0019B968(struct S *p, int n, void *pv);
void func_0019CE68(struct S *p) {
    func_001F3BF8(p);
    p->x1d8 = func_00231138(0x320, 0x10);
    if (p->a) func_0028F068(p, p->a, 2);
    if (p->b) func_0028F068(p, p->b, 2);
    func_0019B968(p, 6, p->x220);
}

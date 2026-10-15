// Resolve type-specific and shared object identifiers, collect up to 16 matching objects, and initialize the completed collection.
// Reference algorithm: src/hand/func_00201DC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S {
    char pad[0x30];
    int n30;
    void *a34[16];
    char pad2[0xA4 - 0x74];
    void *nA4;
    void **pA8;
    void *nAC;
    void *nB0;
};
int func_0013B500(void *a, int b);
void *func_0017E1B8(void *p, int a, int b, void *owner);
int func_0017E208(void *p, int a, int b, void *owner, int d, void **e);
void func_0024BD80(struct S *p);
void func_0024BCC0(struct S *p) {
    if (func_0013B500(*p->pA8, 0x34)) {
        p->nAC = func_0017E1B8(D_00475480, 0x405, 0x40F, 0);
        p->nB0 = func_0017E1B8(D_00475480, 0x405, 0x412, 0);
    }
    p->nA4 = func_0017E1B8(D_00475480, 0x405, 0x6D3, 0);
    p->n30 = func_0017E208(D_00475480, 0x405, 0x2B, 0, 16, p->a34);
    func_0024BD80(p);
}

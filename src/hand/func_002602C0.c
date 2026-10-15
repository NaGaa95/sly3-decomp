// Reset collection state, resolve identifiers in both record arrays, and retain each successful object pointer.
// Reference algorithm: src/hand/func_00211EC0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct G;
extern struct G D_00475480;
struct B {
    int id;
    void *p;
};
struct S {
    char pad[0x120];
    int c110;
    struct B a114[0x10];
    int c194;
    struct B a198[1];
};
void func_00260930(struct S *p);
void *func_0017E1B8(struct G *g, int k, int id, void *owner);
void func_002602C0(struct S *p) {
    int i;
    func_00260930(p);
    for (i = 0; i < p->c194; i++) {
        void *q = func_0017E1B8(&D_00475480, 5, p->a198[i].id, 0);
        if (q) p->a198[i].p = q;
    }
    for (i = 0; i < p->c110; i++) {
        void *q = func_0017E1B8(&D_00475480, 5, p->a114[i].id, 0);
        if (q) p->a114[i].p = q;
    }
}

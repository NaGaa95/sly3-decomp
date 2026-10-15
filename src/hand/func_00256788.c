// Resolve each source identifier into an object, compact the successful results, and update the result count.
// Reference algorithm: src/hand/func_0020AAA8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S {
    char pad[0x1034];
    int a[8];
    int n;
    void *b[8];
    int c;
};
void *func_0017E1B8(void *p, int k, int x, struct S *ps);
void func_00256788(struct S *p) {
    int i;
    p->c = 0;
    for (i = 0; i < p->n; i++) {
        void *r = func_0017E1B8(D_00475480, 4, p->a[i], p);
        if (r) p->b[p->c++] = r;
    }
}

// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct D {
    int a;
    int ib;
};
extern char D_00475480[];
void *func_0017E1B8(void *, int, int, void *);
void func_00150860(char *p, struct D *pd) {
    *(void **)(p + pd->ib) = func_0017E1B8(D_00475480, 4, pd->a, p);
}

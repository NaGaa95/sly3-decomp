// Sly 2 reference: src/hand/func_0013B7B8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
void func_00292540(void *, int, int, int (*)(const void *, const void *));
int D_0014CD60(const void *, const void *);
void func_0014CD78(void *unused, int *pc, int *a) {
    int n = *pc;
    int *pDst, *pSrc, *pMax;
    if (n < 2) return;
    func_00292540(a, n, 4, D_0014CD60);
    pDst = a;
    pMax = a + n;
    for (pSrc = a; pSrc < pMax; pSrc++) {
        if (*pDst != *pSrc) *++pDst = *pSrc;
    }
    *pc = pDst - a + 1;
}

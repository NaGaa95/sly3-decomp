// Reference algorithm: src/hand/func_0019F220.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_0017E208(void *, int, int, int, int, int *);
void func_002514D8(int, void *);
void func_001C01A8(void *p, void *x) {
    int ap[32];
    int c, i;
    c = func_0017E208(p, 0x105, 0x3A, 0, 32, ap);
    for (i = 0; i < c; i++) func_002514D8(ap[i], x);
}

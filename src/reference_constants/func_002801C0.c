// Reference algorithm: src/hand/func_002288D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void func_0025D350(void *pq, void *a, int n, void *b, int c, int d, int e, int f);
void func_002801C0(char *p, int c, int d, int e, int f)
{
    if (c) func_0025D350(D_00475480, p + 0xD4, 4, p + 0xD0, c, d, e, f);
}

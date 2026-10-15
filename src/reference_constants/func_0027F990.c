// Reference algorithm: src/hand/func_002280D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x120]; int f; };
extern char D_00475480[];
int func_0017E208(void *g, int a, int b, int c, int n, struct O **ap);
struct O *func_0027F990(void)
{
    struct O *ap[32];
    struct O *r = 0;
    int n = func_0017E208(D_00475480, 5, 0x18, 0, 0x20, ap);
    int i;
    for (i = 0; i < n; i++) if (ap[i]->f) r = ap[i];
    return r;
}

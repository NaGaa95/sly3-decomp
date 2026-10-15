// Reference algorithm: src/hand/func_001623D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a[7]; };
void func_00185C30(void *p, struct E *pe, void *q, int n);
void func_00185DB0(void *p, void *q, int c, struct E *ae, int n)
{
    int i;
    for (i = 0; i < c; i++)
        func_00185C30(p, &ae[i], q, n);
}

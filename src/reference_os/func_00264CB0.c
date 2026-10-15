// Actual nullable sixteen-bit text pointer and sixteen-bit cursor semantics.
// Sly 2 reference: src/hand/func_00215E30.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
void func_00264B18(void *p, const unsigned short *text);
unsigned short func_00264BB0(void *p);
int func_00264CB0(void *p)
{
    int n = 0;
    func_00264B18(p, 0);
    while (func_00264BB0(p))
        n++;
    return n;
}

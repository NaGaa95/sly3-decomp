// Reference algorithm: src/hand/func_0016D698.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct D { int a; char *b; int c; char *d; };
struct H { short a; short b; };
void func_00193638(int n, struct D *pd, struct H **pph)
{
    struct H *ph = (*pph)++;
    ph->a = n;
    ph->b = ((pd->d - pd->b) >> 4) + 0x24;
}

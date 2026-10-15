// Reference algorithm: src/hand/func_001EA688.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { int n0; unsigned char b4; unsigned char b5; };
int func_00233C90(struct S *p)
{
    switch (p->b4) {
    case 1:
        return 2;
    case 7:
        if (!(p->b5 & 0x10)) return 3;
        return 2;
    }
    return 1;
}

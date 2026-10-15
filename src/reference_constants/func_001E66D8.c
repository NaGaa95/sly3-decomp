// Reference algorithm: src/hand/func_001BC530.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD8]; int c; };
int func_001E66D8(struct S *p, int n)
{
    int c = p->c;
    int r = n % c;
    if (r < 0) r = r + (c - 1);
    else if (r == c - 1) r = 0;
    return r;
}

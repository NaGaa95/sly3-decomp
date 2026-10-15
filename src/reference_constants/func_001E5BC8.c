// Reference algorithm: src/hand/func_001BBA18.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x13C]; int n; };
struct R { int a; int b; };
extern char D_00324BA8[];
struct R *func_001E6018(struct S *p, void *k);
void func_001E5BC8(struct S *p, int x)
{
    if (p->n != -1) {
        struct R *r = func_001E6018(p, D_00324BA8);
        if (r && x) r->b = x;
    }
}

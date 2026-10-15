// Reference algorithm: src/hand/X509v3_data_type_by_NID.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { int a; int unknown4; int b; };
struct X *func_001FBFF0(int n);
int func_001FC0B8(int n)
{
    struct X *p = func_001FBFF0(n);
    if (p)
        return p->b;
    return 0;
}

// Reference algorithm: src/hand/X509v3_data_type_by_NID.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { int a; int unknown4; int b; };
struct X *func_00170528(int n);
int func_00170500(int n)
{
    struct X *p = func_00170528(n);
    if (p)
        return p->b;
    return -1;
}

// Reference algorithm: src/hand/func_0021FB18.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct B { int a; void *p; };
int func_0013B500(void *p, int k);
int func_0025CDD0(void *a, struct B *b);
int func_002725D0(void *a, struct B *b)
{
    if (func_0013B500(b->p, 0x65))
        return 1;
    return func_0025CDD0(a, b);
}

// Reference algorithm: src/hand/func_00210408.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_0017E1B8(void *pv, int k, int id, void *ctx);
int func_0013B500(void *p, int cid);
void func_00240000(void *p, void *q);
void func_00240080(void *p, void *q);
void func_0025D8A8(void *pv, int f, int id, void *q, void *pdef, void *ctx)
{
    void *p;
    if (id == -1)
        p = pdef;
    else
        p = func_0017E1B8(pv, 4, id, ctx);
    if (p && func_0013B500(p, 0x2F)) {
        if (f)
            func_00240000(p, q);
        else
            func_00240080(p, q);
    }
}

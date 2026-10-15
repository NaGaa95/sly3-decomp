// Reference algorithm: src/hand/func_001649D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x54]; void *f64; void *f68; };
struct G { char pad[0x4044]; struct X *f3b0c; };
extern struct G D_00475480;
int func_0017E208(struct G *pg, int kind, int n, int m, int c, void **apv);
int func_00188A38(void *p);
void func_00186298(struct X *p);
void func_00186248(struct X *p);
void func_00189640(void)
{
    struct X *apx[256];
    struct X *pxFound = 0;
    int c = func_0017E208(&D_00475480, 5, 0xA8, 0, 0x100, (void **)apx);
    int i;
    for (i = 0; i < c; i++) {
        struct X *px = apx[i];
        if (func_00188A38(px->f64) && !func_00188A38(px->f68))
            pxFound = px;
    }
    if (pxFound != D_00475480.f3b0c) {
        if (D_00475480.f3b0c)
            func_00186298(D_00475480.f3b0c);
        if (pxFound)
            func_00186248(pxFound);
    }
}

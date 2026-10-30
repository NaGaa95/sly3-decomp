// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_00165C98); Sly 3 adds a final sort of the output list.
struct ALLOCREQ { int cb; int nKind; };
class CTX {
public:
    int a[4];
    CTX();
    ~CTX();
};
struct X { char pad[0x84]; int f84; char pad2[0x104 - 0x88]; int f104; };
struct G { char pad[0x402C]; int c; };
extern "C" {
extern G D_00475480;
void *func_001D2670(ALLOCREQ *preq);
int func_0017E208(G *pg, int kind, int n, int m, int c, void **apv);
void func_00188B08(X *px, int *pc, void *pv, int a, int b);
int func_0018A890(const void *a, const void *b);
void func_00292540(void *base, int n, int size, int (*cmp)(const void *, const void *));
}
extern "C" void func_0018A900(int *pc, void **ppv)
{
    ALLOCREQ req;
    G *pg = &D_00475480;
    *pc = 0;
    req.cb = pg->c * 4;
    req.nKind = 0x10;
    *ppv = func_001D2670(&req);
    CTX ctx;
    req.cb = pg->c * 4;
    req.nKind = 0x10;
    X **apx = (X **)func_001D2670(&req);
    int c = func_0017E208(pg, 5, 0xA9, 0, pg->c, (void **)apx);
    int i;
    for (i = 0; i < c; i++)
        apx[i]->f104 = 0;
    for (int j = 0; j < c; j++) {
        if (!apx[j]->f84)
            func_00188B08(apx[j], pc, *ppv, 0, 0);
    }
    func_00292540(*ppv, *pc, 4, func_0018A890);
}

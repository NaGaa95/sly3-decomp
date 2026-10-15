// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct AR { int cb; int cbAlign; };
void *func_001D25B0(struct AR *par);
void *func_00292034(void *p, int b, int cb);
extern void *D_00474FB8;
extern void *D_00474FC0;
extern int D_00474FB4;
extern int D_00474FBC;
void func_00236AE0(void)
{
    struct AR ar;
    void **pp1 = &D_00474FB8;
    void **pp2 = &D_00474FC0;
    ar.cb = 0xFFF4;
    ar.cbAlign = 0x10;
    *pp1 = func_001D25B0(&ar);
    func_00292034(*pp1, 0, 0xFFF4);
    ar.cb = 0xFFF4;
    ar.cbAlign = 0x10;
    *pp2 = func_001D25B0(&ar);
    func_00292034(*pp2, 0, 0xFFF4);
    D_00474FB4 = D_00474FBC = 0;
}

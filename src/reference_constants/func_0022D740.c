// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x16C]; int n; };
void func_0028FE20(struct S *p, void *source);
void func_0022F450(struct S *p, int n);
void func_0022D740(struct S *p, void *source)
{
    func_0028FE20(p, source);
    if (p->n) {
        p->n = 0;
        func_0022F450(p, 0);
    }
}

// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* frame-info registration thunks (crt): func_0029EA58(&D_0034E618, &D_004D2A00) / func_0029EA80(&D_0034E618) */
extern char D_0034E618[];
extern char D_004D2A00[];
void func_0029EA58(void *begin, void *ob);
void *func_0029EA80(void *begin);
void func_002B3908(void)
{
    func_0029EA58(D_0034E618, D_004D2A00);
}

// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* libmpeg tail-call thunks: func_002AE460(a0, &table) */
extern char D_0032C940[];
extern char D_0032C970[];
int func_002AE460(void *mp, void *tbl);
void func_002B2AC0(void *mp)
{
    func_002AE460(mp, D_0032C940);
}

void func_002B2AD0(void *mp)
{
    func_002AE460(mp, D_0032C970);
}

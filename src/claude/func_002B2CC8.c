// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* libmpeg tail-call thunks: func_002AE460(a0, &table) */
extern char D_0032C988[];
extern char D_0032C9C0[];
int func_002AE460(void *mp, void *tbl);
void func_002B2CC8(void *mp)
{
    func_002AE460(mp, D_0032C988);
}

void func_002B2CD8(void *mp)
{
    func_002AE460(mp, D_0032C9C0);
}

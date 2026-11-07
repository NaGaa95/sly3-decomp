// Sly 2 counterpart: func_00238CC8 (decomp src/lib/func_00238CC8.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
extern int D_0034A6B4;
extern char D_004CC800[];
extern int D_004CC880[];
extern int D_004CC840[];
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_00297948(void *addr)
{
    if (D_0034A6B4 < 0)
        return 0;
    D_004CC880[0] = (int)addr;
    if (func_00295F08(D_004CC800, 2, 0, D_004CC880, 4, D_004CC840, 4, 0, 0) < 0)
        return -1;
    return D_004CC840[0];
}

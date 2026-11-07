// Sly 2 counterpart: sceCdGetDiskType2 (decomp src/lib/sceCdGetDiskType2.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
extern char D_0034DF00[];
extern int D_0034D580[];
extern int D_0034C3AC;
int func_002A0590(int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002936C0(int);
int func_002A10D8(void)
{
    int r;
    if (func_002A0590(3) == 0)
        return -1;
    if (func_00295F08(D_0034DF00, 4, 0, 0, 0, D_0034D580, 4, 0, 0) >= 0) {
        r = *(int *)((unsigned int)D_0034D580 | 0x20000000);
        func_002936C0(D_0034C3AC);
        return r;
    }
    func_002936C0(D_0034C3AC);
    return -1;
}

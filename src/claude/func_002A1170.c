// Sly 2 counterpart: sceCdBreak (decomp src/lib/sceCdBreak.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
extern char D_0034DF00[];
extern int D_0034D580[];
extern volatile int D_0034C3AC;
extern volatile int _sceCd_mode;
int func_002A0590(int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002936C0(int);
int func_002A1170(void)
{
    int r;
    if (func_002A0590(0x1E) == 0)
        return 0;
    _sceCd_mode = 8;
    if (func_00295F08(D_0034DF00, 0x16, 0, 0, 0, D_0034D580, 4, 0, 0) >= 0) {
        _sceCd_mode = 0;
        r = *(int *)((unsigned int)D_0034D580 | 0x20000000);
        func_002936C0(D_0034C3AC);
        return r;
    }
    func_002936C0(D_0034C3AC);
    _sceCd_mode = 0;
    return 0;
}

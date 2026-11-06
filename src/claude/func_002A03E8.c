// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64
// Reference: Sly 2 src/lib/sceCdNcmdDiskReady.c; target Sly 3 0x002A03E8.
extern char D_0034D550[];
extern int D_0034C400[];
extern int D_0034C3A8;
int func_002A0290(int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002936C0(int);
int func_002A03E8(void)
{
    int r;
    if (func_002A0290(2) == 0)
        return 0;
    if (func_00295F08(D_0034D550, 14, 0, 0, 0, D_0034C400, 4, 0, 0) >= 0) {
        r = *(int *)((unsigned int)D_0034C400 | 0x20000000);
        func_002936C0(D_0034C3A8);
        return r;
    }
    func_002936C0(D_0034C3A8);
    return 0;
}

// Sly 2 counterpart: sceCdMmode (decomp src/lib/sceCdMmode.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern char D_0034DF00[];
extern int D_0034D580[];
extern int D_0034D9C0[];
extern volatile int D_0034C3AC;
extern int D_0034DF28, D_0034DF2C, D_0034DF30;
int func_002A0590(int);
void func_00299DF0(void *, int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002936C0(int);
int func_002A1228(int media)
{
    int r;
    int *p = D_0034D9C0;
    if (func_002A0590(0x22) == 0)
        return 0;
    D_0034D9C0[0] = media;
    func_00299DF0(p, 4);
    if (func_00295F08(D_0034DF00, D_0034DF28, 0, p, D_0034DF2C, D_0034D580, D_0034DF30, 0, 0) < 0) {
        func_002936C0(D_0034C3AC);
        return 0;
    }
    r = *(int *)((unsigned int)D_0034D580 | 0x20000000);
    func_002936C0(D_0034C3AC);
    return r;
}

// Sly 2 counterpart: sceMcClose (decomp src/lib/sceMcClose.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct { char p[0x24]; int server; } RpcCD;
extern RpcCD D_004D1200;
extern int D_004D1280[];
extern int D_004D27C0[];
extern int D_0034DF94;
extern int _mc_errno;
void func_002A24D0(void *);
int func_002936F0(int);
int func_002936C0(int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A2648(int fd)
{
    if (D_004D1200.server == 0)
        return -100;
    if (func_002936F0(D_0034DF94) < 0)
        return -200;
    D_004D1280[0] = fd;
    if (func_00295F08(&D_004D1200, 3, 1, D_004D1280, 0x30, D_004D27C0, 4, func_002A24D0, 0) == 0) {
        _mc_errno = 3;
        return 0;
    }
    func_002936C0(D_0034DF94);
    return -91;
}

// Sly 2 counterpart: sceMcDelete (decomp src/lib/sceMcDelete.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int port; int slot; int flags; int size; int offset; char name[0x400]; } McSend;
extern RpcCD D_004D1200;
extern McSend D_004D12B0;
extern int D_004D27C0[];
extern int D_0034DF94;
extern int _mc_errno;
void func_002A24D0(void *);
int func_002936F0(int);
int func_002936C0(int);
char *func_002922B8(char *, const char *, unsigned int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A2F10(int port, int slot, const char *name)
{
    if (D_004D1200.server == 0)
        return -100;
    if (func_002936F0(D_0034DF94) < 0)
        return -200;
    if (name == 0 || name[0] == 0) {
        func_002936C0(D_0034DF94);
        return -210;
    }
    func_002922B8(D_004D12B0.name, name, 0x3FF);
    D_004D12B0.port = port;
    D_004D12B0.slot = slot;
    D_004D12B0.name[0x3FF] = 0;
    D_004D12B0.flags = 0;
    if (func_00295F08(&D_004D1200, 0xF, 1, &D_004D12B0, 0x414, D_004D27C0, 4, func_002A24D0, 0) == 0) {
        _mc_errno = 0xF;
        return 0;
    }
    func_002936C0(D_0034DF94);
    return -91;
}

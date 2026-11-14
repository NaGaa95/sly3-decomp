// Sly 2 counterpart: sceMcGetInfo (decomp src/lib/sceMcGetInfo.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int fd; int port; int slot; int format; int free; int type; int x18; void *param; } McInfoSend;
extern RpcCD D_004D1200;
extern McInfoSend D_004D1280;
extern int D_004D27C0[];
extern char D_004D1700[];
extern int *D_004D1228;
extern int *D_004D122C;
extern int *D_004D1230;
extern int D_0034DF94;
extern int _mc_errno;
void func_002A2B10(void *);
int func_002936F0(int);
int func_002936C0(int);
void func_00299DF0(void *, int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A2B68(int port, int slot, int *type, int *free, int *format)
{
    if (D_004D1200.server == 0)
        return -100;
    if (func_002936F0(D_0034DF94) < 0)
        return -200;
    D_004D1280.port = port;
    D_004D1280.slot = slot;
    D_004D1280.param = D_004D1700;
    if (type) D_004D1280.type = 1; else D_004D1280.type = 0;
    if (free) D_004D1280.free = 1; else D_004D1280.free = 0;
    if (format) D_004D1280.format = 1; else D_004D1280.format = 0;
    D_004D1228 = type;
    D_004D122C = free;
    D_004D1230 = format;
    func_00299DF0(D_004D1700, 0xC0);
    if (func_00295F08(&D_004D1200, 1, 1, &D_004D1280, 0x30, D_004D27C0, 4, func_002A2B10, D_004D1700) != 0) {
        func_002936C0(D_0034DF94);
        return -91;
    }
    _mc_errno = 1;
    return 0;
}

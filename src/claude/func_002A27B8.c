// Sly 2 counterpart: sceMcRead (decomp src/lib/sceMcRead.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
// (Claude agent) MATCH with -fstrict-aliasing (-Os sweep)
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int fd; int x4; int x8; int size; int x10; int x14; void *buf; void *param; } McRwSend;
extern RpcCD D_004D1200;
extern McRwSend D_004D1280;
extern int D_004D27C0[];
extern char D_004D1700[];
extern int D_0034DF94;
extern int _mc_errno;
void func_002A2708(void *);
int func_002936F0(int);
int func_002936C0(int);
void func_00299DF0(void *, int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A27B8(int fd, void *buf, int size)
{
    if (D_004D1200.server == 0)
        return -100;
    if (func_002936F0(D_0034DF94) < 0)
        return -200;
    D_004D1280.fd = fd;
    D_004D1280.buf = buf;
    D_004D1280.size = size;
    D_004D1280.param = D_004D1700;
    func_00299DF0(buf, size);
    func_00299DF0(D_004D1700, 0xC0);
    if (func_00295F08(&D_004D1200, 5, 1, &D_004D1280, 0x30, D_004D27C0, 4, func_002A2708, D_004D1700) == 0) {
        _mc_errno = 5;
        return 0;
    }
    func_002936C0(D_0034DF94);
    return -91;
}

// Sly 2 counterpart: sceMcWrite (decomp src/lib/sceMcWrite.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
typedef struct { int fd; int x4; int x8; int size; int x10; unsigned head; void *buf; int x1c; unsigned char data[16]; } McRwSend;
extern RpcCD D_004D1200;
extern McRwSend D_004D1280;
extern int D_004D27C0[];
extern int D_0034DF94;
extern int _mc_errno;
void func_002A24D0(void *);
int func_002936F0(int);
int func_002936C0(int);
void func_00293920(int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A28D0(int fd, const void *buf, int size)
{
    unsigned i;
    if (D_004D1200.server == 0)
        return -100;
    if (func_002936F0(D_0034DF94) < 0)
        return -200;
    D_004D1280.fd = fd;
    if (size <= 16) {
        D_004D1280.head = size;
        D_004D1280.size = 0;
        D_004D1280.buf = 0;
    } else {
        unsigned lo = (unsigned)buf - 16;
        unsigned n = (((unsigned)buf - 1) & 0xFFFFFFF0u) - lo;
        D_004D1280.size = size - n;
        D_004D1280.head = n;
        D_004D1280.buf = (char *)buf + n;
    }
    for (i = 0; i < D_004D1280.head; i++)
        D_004D1280.data[i] = ((unsigned char *)buf)[i];
    func_00293920(0);
    if (func_00295F08(&D_004D1200, 6, 1, &D_004D1280, 0x30, D_004D27C0, 4, func_002A24D0, 0) != 0) {
        func_002936C0(D_0034DF94);
        return -91;
    }
    _mc_errno = 6;
    return 0;
}

// Sly 2 counterpart: sceClose (decomp src/lib/sceClose.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
struct iob { int fd, busy, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { int sema; int *res; int rsize; int fd; int idx; } CloseArg;
extern int D_0034A69C;
extern CloseArg D_004CB000;
extern struct iob D_004CC500[];
extern char D_004CC700[];
extern int D_004CBC40[];
extern char D_0032AAB8[];
struct iob *func_00296350(int);
int func_002967D0(int);
void func_00296800(void);
int func_002936A0(struct SemaParam *);
int func_002936B0(int);
int func_002936E0(int);
int func_00296260(void *, int, int, void *, int, void *, int, void *, void *, int);
int func_00296DB8(int fd)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    CloseArg *arg;
    int sema, r;

    arg = &D_004CB000;
    io = func_00296350(fd);
    func_002967D0(1);
    if (D_0034A69C == 0 || io == 0 || io->busy == 0) {
        func_00296800();
        return -9;
    }
    arg->fd = io->fd;
    arg->idx = io - D_004CC500;
    sp.maxCount = 1;
    sp.option = (unsigned int)D_0032AAB8;
    sp.initCount = 0;
    sema = func_002936A0(&sp);
    D_004CB000.sema = sema;
    arg->res = &res;
    arg->rsize = 4;
    if (func_00296260(D_004CC700, 1, 0, arg, 0x14, D_004CBC40, 4, 0, 0, 0) < 0) {
        func_002936B0(sema);
        func_00296800();
        return -11;
    }
    io->busy = 0;
    r = *(volatile int *)((unsigned int)D_004CBC40 | 0x20000000);
    func_00296800();
    if (r == 0) {
        func_002936B0(sema);
        return -11;
    }
    func_002936E0(sema);
    func_002936B0(sema);
    if (res > -1) return 0;
    return res;
}

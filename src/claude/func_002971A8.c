// Sly 2 counterpart: sceWrite (decomp src/lib/sceWrite.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* libkernel fileio func_002971A8. Keys: `nowait` assigned in a nested
   do{do{}while(0);}while(0) after `i = 0` (loop-depth weight gives the target's s4 nowait > s5 sema > s6 size > s7 flags
   priority); a separate counter j for the head-copy loop; and a dead first statement in each arm (`r = (int)D_0034A618;`,
   `n = buf & 0xF;`): it computes the arm's `lui`/andi itself, so gcse PRE no longer appends it AFTER `i = 0` / `nowait = 0`. */
struct iob { int fd, flags, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { int sema; int *res; int rsize; int fd; void *buf; int size; int nhead; char head[16]; int idx; } WriteArg;
extern int D_0034A69C;
extern int D_0034A6AC;
extern int D_0034A618[32];
extern WriteArg D_004CB000;
extern struct iob D_004CC500[];
extern char D_004CC700[];
extern int D_004CBC40[];
extern char D_0032AB00[];
struct iob *func_00296350(int);
int func_002967D0(int);
void func_00296800(void);
void func_00299DF0(void *, int);
int func_002936A0(struct SemaParam *);
int func_002936B0(int);
int func_002936C0(int);
int func_002936E0(int);
int func_00296260(void *, int, int, void *, int, void *, int, void *, void *, int);
int func_002971A8(int fd, const void *buf, int size)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    WriteArg *arg;
    int sema, r, flags, nowait, i, n, j;

    arg = &D_004CB000;
    io = func_00296350(fd);
    func_002967D0(3);
    if (D_0034A69C == 0 || io == 0 || (flags = io->flags) == 0) {
        func_00296800();
        return -9;
    }
    arg->fd = io->fd;
    arg->idx = io - D_004CC500;
    sp.maxCount = 1;
    sp.option = (unsigned int)D_0032AB00;
    arg->size = size;
    arg->buf = (void *)buf;
    sp.initCount = 0;
    sema = func_002936A0(&sp);
    arg->res = &res;
    arg->rsize = 4;
    D_004CB000.sema = sema;
    if (flags & 0x8000) {
        func_002936E0(D_0034A6AC);
        r = (int)D_0034A618;
        i = 0;
        do { do { nowait = flags & 0x8000; } while (0); } while (0);
        for (; i < 32; i++) {
            if (D_0034A618[i] == -1) {
                D_0034A618[i] = arg->sema;
                arg->sema = -arg->sema;
                break;
            }
        }
        func_002936C0(D_0034A6AC);
    } else {
        n = (unsigned int)buf & 0xF;
        nowait = 0;
    }
    if (((unsigned int)buf & 0xF) == 0)
        n = 0;
    else
        n = (unsigned int)buf / 16 * 16 + 16 - (unsigned int)buf;
    if (size < n)
        n = size;
    if (!(flags & 0x20000000))
        func_00299DF0((void *)buf, size);
    buf = (void *)((unsigned int)buf | 0x20000000);
    arg->nhead = n;
    for (j = 0; j < n; j++)
        arg->head[j] = ((const char *)buf)[j];
    if (func_00296260(D_004CC700, 3, 0, &D_004CB000, 0x30, D_004CBC40, 4, 0, 0, nowait) < 0) {
        func_002936B0(sema);
        func_00296800();
        return -11;
    }
    r = *(volatile int *)((unsigned int)D_004CBC40 | 0x20000000);
    func_00296800();
    if (r == 0) {
        func_002936B0(sema);
        return -11;
    }
    if (nowait) {
        func_002936B0(sema);
        return 0;
    }
    func_002936E0(sema);
    func_002936B0(sema);
    return res;
}

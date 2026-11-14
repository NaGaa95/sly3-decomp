// Sly 2 counterpart: sceRead (decomp src/lib/sceRead.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* libkernel fileio func_00296F38. Keys: `nowait` assigned in a nested do{do{}while(0);}while(0) after
   `i = 0` (global-alloc priority); and the dead `r = (int)<table>` first statement of each arm: it computes the arm's
   `lui` itself, so gcse PRE no longer appends it AFTER `i = 0` / `nowait = 0` (the target has lui first in both arms). */
struct iob { int fd, flags, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { int sema; int *res; int rsize; int fd; void *buf; int size; int x18; int idx; } ReadArg;
extern int D_0034A69C;
extern int D_0034A6AC;
extern int D_0034A618[32];
extern ReadArg D_004CB000;
extern struct iob D_004CC500[];
extern char D_004CC700[];
extern int D_004CBC40[];
extern char D_0032AAE8[];
struct iob *func_00296350(int);
int func_002967D0(int);
void func_00296800(void);
void func_00299DF0(void *, int);
int func_002936A0(struct SemaParam *);
int func_002936B0(int);
int func_002936C0(int);
int func_002936E0(int);
int func_00296260(void *, int, int, void *, int, void *, int, void *, void *, int);
int func_00296F38(int fd, void *buf, int size)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    ReadArg *arg;
    int sema, r, flags, nowait, i;

    arg = &D_004CB000;
    io = func_00296350(fd);
    func_002967D0(2);
    if (D_0034A69C == 0 || io == 0 || (flags = io->flags) == 0) {
        func_00296800();
        return -9;
    }
    arg->fd = io->fd;
    arg->idx = io - D_004CC500;
    sp.maxCount = 1;
    sp.option = (unsigned int)D_0032AAE8;
    arg->buf = buf;
    arg->size = size;
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
        r = (int)D_004CBC40;
        nowait = 0;
    }
    if (!(flags & 0x20000000))
        func_00299DF0(buf, size);
    func_00299DF0(arg, 0x20);
    if (func_00296260(D_004CC700, 2, 0, &D_004CB000, 0x20, D_004CBC40, 4, 0, 0, nowait) < 0) {
        func_002936B0(sema);
        func_00296800();
        return -11;
    }
    r = *(int *)((unsigned int)D_004CBC40 | 0x20000000);
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

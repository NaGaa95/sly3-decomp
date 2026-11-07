// Sly 2 counterpart: sceOpen (decomp src/lib/sceOpen.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
#define va_arg(ap, T) (*(T *)((ap += 8) - 8))
struct iob { int fd, flags, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { int sema; int *res; int rsize; int flags; int mode; char name[0x400]; int idx; } OpenArg;
extern int D_0034A69C;
extern int D_0034A6A8;
extern OpenArg D_004CB000;
extern struct iob D_004CC500[];
extern char D_004CC700[];
extern int D_004CBC40[];
extern char D_0032AAA0[];
int func_002967D0(int);
void func_00296800(void);
void func_00296858(void);
int func_00296A60(void);
struct iob *func_002961D8(void);
int func_002936A0(struct SemaParam *);
int func_002936B0(int);
int func_002936C0(int);
int func_002936E0(int);
int func_00296260(void *, int, int, void *, int, void *, int, void *, void *, int);
int func_00296B28(const char *name, int flags, ...)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    OpenArg *arg;
    int sema, r, i, mode, idx;
    va_list ap;

    va_start(ap, flags);
    arg = &D_004CB000;
    func_002967D0(0);
    if (D_0034A69C == 0)
        func_00296858();
    if (func_00296A60()) {
        func_00296800();
        return -0x10004;
    }
    io = func_002961D8();
    if (io == 0) {
        func_00296800();
        return -19;
    }
    mode = va_arg(ap, int);
    for (i = 0; i < 0x400; i++) {
        if ((arg->name[i] = name[i]) == 0) break;
    }
    if (i == 0x400)
        arg->name[0x3FF] = 0;
    idx = io - D_004CC500;
    arg->flags = flags & 0x7FFFFFFF;
    arg->mode = mode;
    sp.maxCount = 1;
    sp.option = (unsigned int)D_0032AAA0;
    arg->idx = idx;
    sp.initCount = 0;
    sema = func_002936A0(&sp);
    arg->res = &res;
    arg->sema = sema;
    arg->rsize = 4;
    if (func_00296260(D_004CC700, 0, 0, &D_004CB000, 0x418, D_004CBC40, 4, 0, 0, 0) < 0) {
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
    func_002936E0(sema);
    func_002936B0(sema);
    if (res < 0) {
        func_002936E0(D_0034A6A8);
        io->flags = 0;
        func_002936C0(D_0034A6A8);
        return res;
    }
    r = idx;
    func_002936E0(D_0034A6A8);
    io->fd = res;
    io->flags |= flags;
    func_002936C0(D_0034A6A8);
    return r;
}

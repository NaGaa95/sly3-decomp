// Sly 2 counterpart: sceIoctl (decomp src/lib/sceIoctl.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* libkernel fileio func_00297468. Keys: `volatile` sema table D_0034A618 (case-1 loop); the request
   dispatch is written as the switch's own decision tree (==2, <3, ==1, ==3) with the case-1 constant in a local `one`
   set at entry - that is what keeps 1 in $s5 from the prologue; arg->sema is stored before res/rsize (gcc rotates it
   into the jal delay slot). */
struct iob { int fd, flags, x8, xC; };
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
typedef struct { char b[0x400]; } IoctlData;
typedef struct { int sema; int *res; int rsize; int fd; int req; IoctlData data; int x414; int x418; int size; } IoctlArg;
typedef struct { char b[0x440]; } FsStat;
extern int D_0034A69C;
extern int D_0034A698;
extern int D_0034A6AC;
extern volatile int D_0034A618[32];
extern void *D_004CAFC8;
extern IoctlArg D_004CB000;
extern FsStat D_004CBC90[];
extern char D_004CC700[];
extern int D_004CBC40[];
extern char D_0032AB18[];
struct iob *func_00296350(int);
int func_002967D0(int);
void func_00296800(void);
void func_00296858(void);
void func_00299DF0(void *, int);
int func_002936A0(struct SemaParam *);
int func_002936B0(int);
int func_002936C0(int);
int func_002936E0(int);
int func_00296260(void *, int, int, void *, int, void *, int, void *, void *, int);

int func_00297468(int fd, int req, void *data)
{
    struct SemaParam sp;
    int res;
    struct iob *io;
    IoctlArg *arg;
    int sema, r, i;
    int one = 1;    /* case value held in a register from the prologue, as in the target */

    arg = &D_004CB000;
    io = func_00296350(fd);
    func_002967D0(5);
    D_004CAFC8 = data;
    if (D_0034A69C == 0)
        func_00296858();
    if (io == 0 || io->flags == 0) {
        func_00296800();
        return -9;
    }
    arg->x414 = 0;
    arg->x418 = 0;
    if (req == 2) goto c2;
    if (req < 3) { if (req == one) goto c1; goto dflt; }
    if (req == 3) goto c3;
    goto dflt;
    c1: {
        func_002936E0(D_0034A6AC);
        for (i = 0; i < 32; i++) {
            if (D_0034A618[i] != -1)
                break;
        }
        if (i == 32)
            *(int *)D_004CAFC8 = 0;
        else
            *(int *)D_004CAFC8 = 1;
        func_002936C0(D_0034A6AC);
        func_00296800();
        return 0;
    }
    c2: {
        *(int *)data = *(int *)((unsigned int)&D_004CBC90[D_0034A698] | 0x20000000);
        func_00296800();
        return 0;
    }
    c3: {
        *(long *)data = *(long *)((unsigned int)&D_004CBC90[D_0034A698] | 0x20000000);
        func_00296800();
        return 0;
    }
    dflt:
    arg->fd = io->fd;
    arg->req = req;
    if (data == 0) {
        arg->size = 0;
    } else {
        arg->size = 0x400;
        arg->data = *(IoctlData *)data;
    }
    sp.maxCount = 1;
    sp.option = (unsigned int)D_0032AB18;
    sp.initCount = 0;
    sema = func_002936A0(&sp);
    arg->sema = sema;
    arg->res = &res;
    arg->rsize = 4;
    func_00299DF0(&D_004CB000, 0x420);
    if (func_00296260(D_004CC700, 5, 0, &D_004CB000, 0x420, D_004CBC40, 4, 0, 0, 0) < 0) {
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
    return res;
}

// Sly 2 counterpart: DelayThread (decomp src/lib/DelayThread.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct { int currentCount; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; } SemaParam;
extern char D_0032A7E0[];
int func_002936A0(SemaParam *);
int func_002936B0(int);
int func_002936E0(int);
long func_00299218(int, int);
int func_00299348(long, void *, int);
int _DelayThreadHandler(int, unsigned short, void *);
int func_00294198(int usec)
{
    SemaParam sp;
    int sema;
    int al;
    int st;
    __asm__ volatile("mfc0 %0, $12" : "=r"(st));
    if ((st & 0x10000) == 0)
        return 0x80008008;
    sp.maxCount = 1;
    sp.option = (unsigned int)D_0032A7E0;
    sp.initCount = 0;
    sema = func_002936A0(&sp);
    if (sema < 0)
        return 0x80008003;
    al = func_00299348(func_00299218(0, usec), _DelayThreadHandler, sema);
    if (al >= 0) {
        func_002936E0(sema);
        func_002936B0(sema);
        return 0;
    }
    func_002936B0(sema);
    return al;
}

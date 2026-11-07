// Sly 2 counterpart: InitThread (decomp src/lib/InitThread.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int currentCount; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; } SemaParam;
typedef struct { int status; void *entry; void *stack; int stackSize; void *gpReg; int initPriority; int currentPriority; unsigned int attr; unsigned int option; int waitType; int waitId; int wakeupCount; } ThreadParam;
typedef struct { int x0; int idx; } WQ;
extern char D_0032A7C8[];
extern char D_004C8EC0[];
extern char D_00372DF0[];
extern int D_004C92C0;
extern WQ D_004C92C8;
extern int D_0034A608;
int func_002936A0(SemaParam *);
int func_002936B0(int);
int func_002934A0(ThreadParam *);
int func_00294260(int, void *);
int func_00293590(void);
int func_00293530(int, int);
void func_00293F30(void *);
int func_00294008(void)
{
    ThreadParam tp;
    SemaParam sp;
    char *name;
    if (D_0034A608 > 0)
        goto fail;
    {
        name = D_0032A7C8;
        sp.maxCount = 0xFF;
        sp.initCount = 0;
        sp.option = (unsigned int)name;
        D_004C92C0 = func_002936A0(&sp);
        if (D_004C92C0 < 0)
            goto fail;
        tp.entry = func_00293F30;
        tp.stack = D_004C8EC0;
        tp.stackSize = 0x400;
        tp.gpReg = D_00372DF0;
        tp.option = (unsigned int)name;
        tp.initPriority = 0;
        D_0034A608 = func_002934A0(&tp);
        if (D_0034A608 < 0) {
            func_002936B0(D_004C92C0);
        fail:
            return -1;
        }
        D_004C92C8.x0 = 0;
        D_004C92C8.idx = 0;
        func_00294260(D_0034A608, &D_004C92C8);
        func_00293530(func_00293590(), 1);
    }
    return D_0034A608;
}

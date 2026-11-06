// SLY3_CFLAGS: -Os -G0
// config/functions.csv lumps func_00271C10 (0x271C10-0x271C48), two dead epilogue scraps (0x271C48-0x271C58)
// and the thread starter at 0x271C58 into one entry.
struct LOCK { int c; int owner; int sema; };
int func_002936C0(int sema);
void func_00271C10(struct LOCK *p)
{
    if (--p->c == 0) {
        p->owner = -1;
        func_002936C0(p->sema);
    }
}
struct THREADPARAM { int status; void (*entry)(void *); void *stack; int stackSize; void *gp; int prio; int pad[6]; };
extern struct { int self; int thread; } D_00349F88;
extern char D_004BB220[];
extern char D_00372DF0[];
int func_00293590(void);
int func_00293530(int thread, int prio);
void *func_00292034(void *p, int c, int n);
int func_002934A0(struct THREADPARAM *tp);
void func_001830F8(void *arg);
void func_00271C58(void)
{
    struct THREADPARAM tp;
    D_00349F88.self = func_00293590();
    func_00293530(D_00349F88.self, 5);
    func_00292034(&tp, 0, sizeof(tp));
    tp.stackSize = 0x1000;
    tp.stack = D_004BB220;
    tp.prio = 2;
    tp.gp = D_00372DF0;
    tp.entry = func_001830F8;
    D_00349F88.thread = func_002934A0(&tp);
}

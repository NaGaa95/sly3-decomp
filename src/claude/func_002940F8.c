// Sly 2 counterpart: iWakeupThread (decomp src/lib/iWakeupThread.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char cmd; unsigned char id; } WQE;
typedef struct { int x0; int idx; WQE q[0x200]; } WQ;
extern int D_004C92C0;
extern WQ D_004C92C8;
extern int D_0034A608;
int func_002935E0(int);
int func_002936D0(int);
int func_002940F8(int id)
{
    int cur;
    WQ *q;
    int i;
    __asm__ volatile("addiu $3, $0, -0x2F\n\tsyscall\n\tmove %0, $2" : "=r"(cur) : : "$2", "$3");
    if (cur != id)
        return func_002935E0(id);
    if ((unsigned)cur >= 0x100 || D_0034A608 == 0)
        return -1;
    q = &D_004C92C8;
    i = q->idx & 0x1FF;
    q->idx = i + 1;
    q->q[i].cmd = 0;
    q->q[i].id = cur;
    func_002936D0(D_004C92C0);
    return cur;
}

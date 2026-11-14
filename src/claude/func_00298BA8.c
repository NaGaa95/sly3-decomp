// Sly 2 counterpart: cbTimerHandler (decomp src/lib/cbTimerHandler.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* func_00298BA8 (libkernel timer.c): T2 compare interrupt; runs expired alarms. The callback's $gp is
   loaded from the counter (asm), the inline GetTime is iGetTimerSystemTime; ovf/count volatile as in the target. */
typedef struct Counter {
    struct Counter *next;
    int x4;
    int id;
    unsigned int mode;
    unsigned long base;
    unsigned long x18;
    unsigned long sched;
    unsigned long (*handler)(int, unsigned long, unsigned long, void *, void *);
    void *gp;
    void *arg;
} Counter;
typedef struct {
    volatile unsigned long ovf;  /* 0x00 */
    int pad8[2];
    volatile int count; /* 0x10 */
    Counter *free;      /* 0x14 */
    Counter *head;      /* 0x18 */
    int cur;            /* 0x1C */
} TimerSys;
extern TimerSys D_0034B650;
#define T_COUNT (*(volatile unsigned int *)0x10001000)
#define T_MODE  (*(volatile unsigned int *)0x10001010)
void func_00298740(unsigned int);
Counter *UnlinkAlarm(Counter *);
void func_00298AE8(Counter *);
void func_00298958(unsigned long);

static inline unsigned long GetTime(void)
{
    unsigned int cnt, mode;
    cnt = T_COUNT;
    mode = T_MODE;
    if (mode & 0x800) {
        D_0034B650.ovf++;
        func_00298740(mode & ~0x400);
        cnt = T_COUNT;
    }
    return ((D_0034B650.ovf << 16) | cnt) << ((mode & 3) * 4);
}

int func_00298BA8(int cause, void *arg, void *addr)
{
    Counter *p, *next;
    unsigned long now, target, r;

    if (T_MODE & 0x400) {
        p = D_0034B650.head;
        while (p) {
            target = p->sched + p->base - p->x18;
            now = GetTime();
            if (now < target)
                break;
            next = UnlinkAlarm(p);
            {
                unsigned long dt = now + p->x18 - p->base;
                D_0034B650.cur = ((unsigned int)p << 4) | p->id;
                __asm__ __volatile__("lw $28, %0" : : "m"(p->gp));
                r = p->handler(((unsigned int)p << 4) | p->id, p->sched, dt, p->arg, addr);
            }
            if (r == 0) {
                p->mode &= ~2;
            } else if (r == (unsigned long)-1) {
                p->id = 0;
                p->mode = 0;
                p->next = D_0034B650.free;
                D_0034B650.free = p;
                D_0034B650.count--;
            } else {
                if (r < 0x3999)
                    r = 0x3999;
                p->sched += r;
                func_00298AE8(p);
            }
            p = next;
        }
    }
    D_0034B650.cur = -1;
    func_00298958(GetTime());
    GetTime();
    __asm__ __volatile__("sync\n\tei");
    return 0;
}

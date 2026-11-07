// Sly 2 counterpart: iSetTimerHandler (decomp src/lib/iSetTimerHandler.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int id; unsigned int mode; long base; long x18; long sched; void *handler; void *gp; void *arg; } Counter;
typedef struct { char pad[0x1C]; volatile int cur; } TimerSys;
extern TimerSys D_0034B650;
long func_00298E50(void);
void func_00298AE8(Counter *);
void UnlinkAlarm(Counter *);
void func_00298958(long);
int func_002990A0(int id, long sched, void *handler, void *arg)
{
    Counter *p = (Counter *)(((unsigned int)id >> 10) << 6);
    TimerSys *ts;
    unsigned int mode;
    if (id < 0 || (id & 0x3FF) != p->id)
        return 0x80008002;
    ts = &D_0034B650;
    if (ts->cur == id)
        return 0x80000010;
    mode = p->mode;
    if (mode & 2) {
        UnlinkAlarm(p);
        mode = p->mode;
    }
    p->handler = handler;
    if (handler == 0) {
        p->mode = mode & ~2;
    } else {
        register void *gp __asm__("$28");
        p->sched = sched;
        p->mode = mode | 2;
        p->gp = gp;
        p->arg = arg;
        if (*(volatile unsigned int *)&p->mode & 1)
            func_00298AE8(p);
    }
    func_00298958(func_00298E50());
    return 0;
}

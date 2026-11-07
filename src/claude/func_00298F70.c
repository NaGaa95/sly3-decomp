// Sly 2 counterpart: iStartTimerCounter (decomp src/lib/iStartTimerCounter.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int id; int mode; long base; } Counter;
typedef struct { char pad[0x1C]; volatile int cur; } TimerSys;
extern TimerSys D_0034B650;
long func_00298E50(void);
void func_00298AE8(Counter *);
void func_00298958(long);
int func_00298F70(int id)
{
    Counter *p = (Counter *)(((unsigned int)id >> 10) << 6);
    long t;
    TimerSys *ts;
    if (id < 0 || (id & 0x3FF) != p->id)
        return 0x80008002;
    ts = &D_0034B650;
    if (ts->cur == id)
        return 0x80000010;
    if (p->mode & 1)
        return 1;
    t = func_00298E50();
    p->base = t;
    p->mode |= 1;
    if (p->mode & 2) {
        func_00298AE8(p);
        func_00298958(t);
    }
    return 0;
}

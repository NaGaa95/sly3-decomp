// Sly 2 counterpart: SetTimerAlarm (decomp src/lib/SetTimerAlarm.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct Alarm {
    struct Alarm *next;
    volatile int id;
    void *func;
    void *arg;
} Alarm;
extern Alarm *D_004CF080;
int func_002980D0(void);
int func_00298120(void);
int func_00298F18(void);
int func_00299198(int, long, void *, void *);
int func_00299020(int);
int func_002992E8(int, int, int, Alarm *);
static inline Alarm *AllocAlarm(void)
{
    Alarm *p = D_004CF080;
    if (p)
        D_004CF080 = p->next;
    return p;
}
int func_00299348(long sched, void *func, void *arg)
{
    Alarm *p;
    int id;
    int st;
    if (func == 0)
        return 0x80000016;
    st = func_002980D0();
    p = AllocAlarm();
    if (p == 0) {
        if (st)
            func_00298120();
        return 0x80008005;
    }
    id = func_00298F18();
    if (id < 0) {
        Alarm *h = D_004CF080;
        D_004CF080 = p;
        p->next = h;
        p->id = 0;
        if (st)
            func_00298120();
        return id;
    }
    p->func = func;
    p->arg = arg;
    p->id = id;
    func_00299198(id, sched, func_002992E8, p);
    func_00299020(id);
    if (st)
        func_00298120();
    return ((int)p << 4) | (id & 0xFE) | 1;
}

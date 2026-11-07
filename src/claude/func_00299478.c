// Sly 2 counterpart: iSetTimerAlarm (decomp src/lib/iSetTimerAlarm.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct Alarm {
    struct Alarm *next;
    volatile int id;
    void *func;
    void *arg;
} Alarm;
extern Alarm *D_004CF080;
int func_00298EA8(void);
int func_002990A0(int, long, void *, void *);
int func_00298F70(int);
int func_002992E8(int, int, int, Alarm *);
static inline Alarm *AllocAlarm(void)
{
    Alarm *p = D_004CF080;
    if (p)
        D_004CF080 = p->next;
    return p;
}
int func_00299478(long sched, void *func, void *arg)
{
    Alarm *p;
    int id;
    if (func == 0)
        return 0x80000016;
    p = AllocAlarm();
    if (p == 0)
        return 0x80008005;
    id = func_00298EA8();
    if (id >= 0) {
        p->func = func;
        p->arg = arg;
        p->id = id;
        func_002990A0(id, sched, func_002992E8, p);
        func_00298F70(id);
        return ((int)p << 4) | (id & 0xFE) | 1;
    }
    {
        Alarm *h = D_004CF080;
        D_004CF080 = p;
        p->next = h;
        p->id = 0;
    }
    return id;
}

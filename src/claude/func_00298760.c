// Sly 2 counterpart: InitTimer (decomp src/lib/InitTimer.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -Os -G0
// SLY3_ASM: gnu-reorg
typedef struct Counter { struct Counter *next; int pad[15]; } Counter;
typedef struct { long time; int id; int pad; int x10; Counter *free; } TimerSys;
extern TimerSys D_0034B650;
extern Counter D_004CCC80[128];
void func_00298BA8(void);
void *func_00292034(void *, int, int);
void func_00299298(void);
int func_00293390(int, void *, int, void *);
int func_002980D0(void);
void func_00298730(int);
void func_00298740(int);
void func_00298750(int);
int func_00293DF8(int);
int func_00298120(void);
int func_00298760(int mode)
{
    TimerSys *ts = &D_0034B650;
    Counter *p;
    int i, r, oldei;
    unsigned int m;
    if (ts->id >= 0)
        return 0x80008001;
    ts->time = 0;
    ts->x10 = 0;
    func_00292034(D_004CCC80, 0, sizeof(D_004CCC80));
    ts->free = D_004CCC80;
    {
        Counter *q;
        i = 127;
        p = &D_004CCC80[127];
        q = &D_004CCC80[128];
        for (; i >= 0; i--) {
            p->next = q;
            p--;
            q--;
        }
    }
    D_004CCC80[127].next = 0;
    func_00299298();
    r = func_00293390(0xB, func_00298BA8, 0, 0);
    if (r < 0)
        return 0x80009021;
    D_0034B650.id = r;
    oldei = func_002980D0();
    m = *(volatile unsigned int *)0x10001010;
    m = (m & ~3) | mode;
    m |= 0x300;
    if (!(m & 0x80)) {
        func_00298730(0);
        m |= 0xC80;
        func_00298750(0xFFFF);
    }
    func_00298740(m);
    func_00293DF8(0xB);
    if (oldei) func_00298120();
    return 0;
}

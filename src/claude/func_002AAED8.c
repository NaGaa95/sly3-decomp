// Sly 2 counterpart: _doCSC2 (decomp src/lib/_doCSC2.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { volatile int cnt; int done; int rem; unsigned int addr; int total; } CSC;
typedef struct { int type; int pad[7]; } CB;
typedef struct { char p0[0x868]; void *mp; } D;
#define R(a) (*(volatile unsigned int *)(a))
#define RS(a) (*(volatile int *)(a))
int func_002AB570(int ch, void *arg);
int func_002933C0(int ch, int (*h)(int, void *), int next, void *arg);
int func_002933D0(int ch, int id);
int func_00293EC8(int ch);
int func_00293E60(int ch);
int func_002980D0(void);
int func_00298120(void);
int _sceMpegDispatchMpegCallback(void *mp, CB *cb);
void _sceMpegError(D *d, const char *msg);
void func_002AAED8(D *d, unsigned int out, int n)
{
    CB cb;
    CSC c;
    int id;
    int e;

    c.total = n / 1023 + 1;
    c.rem = n;
    c.addr = (out + 0xFFC00) & 0x0FFFFFFF;
    c.done = 0;
    c.cnt = 0;
    while (RS(0x10002010) < 0)
        ;
    id = func_002933C0(3, func_002AB570, 0, &c);
    R(0x1000E010) = 8;
    func_00293EC8(3);
    e = func_002980D0();
    { volatile unsigned int *m = (void *)0x1000B010, *q = (void *)0x1000B020, *c = (void *)0x1000B000;
    *m = out & 0x0FFFFFFF;
    *q = 0xFFC0;
    *c = 0x100; }
    if (e)
        func_00298120();
    R(0x10002000) = 0x700003FF;
    cb.type = 4;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    while (c.cnt < c.total)
        ;
    if (c.done)
        _sceMpegError(d, "CSC handler error\n");
    while (RS(0x10002010) < 0)
        ;
    func_00293E60(3);
    func_002933D0(3, id);
}

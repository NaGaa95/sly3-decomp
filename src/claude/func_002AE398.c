// Sly 2 counterpart: _sceMpegErrorBdec (decomp src/lib/_sceMpegErrorBdec.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int type; int data[7]; } CB;
typedef struct { char p0[0x868]; void *mp; } D;
void _sceMpegError(D *d, const char *msg);
int _sceMpegDispatchMpegCallback(void *mp, CB *cb);
int func_002980D0(void);
int func_00298120(void);
void func_002AE398(D *d)
{
    CB cb;
    int e;

    _sceMpegError(d, "Error code detected(BDEC)");
    cb.type = 2;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    *(volatile unsigned int *)0x10002010 = 0x40000000;
    cb.type = 3;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    e = func_002980D0();
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 | 0x10000;
    *(volatile unsigned int *)0x1000B000 = 0;
    *(volatile unsigned int *)0x1000F590 = *(volatile unsigned int *)0x1000F520 & ~0x10000;
    if (e) func_00298120();
    *(volatile unsigned int *)0x1000B020 = 0;
}

// Sly 2 counterpart: _sequenceHeader (decomp src/lib/_sequenceHeader.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int type; int pad[7]; } CB;
typedef struct {
    char p0[0xE8]; int xE8;
    char pEC[0x134 - 0xEC]; int hsize; int vsize;
    char p13C[0x144 - 0x13C]; int bit_rate; int vbv_size;
    char p14C[0x828 - 0x14C]; int x828; unsigned int cmd;
    char p830[0x850 - 0x830]; int load_intra; int load_nonintra;
    char p858[0x868 - 0x858]; void *mp;
} D;
#define R(a) (*(volatile unsigned int *)(a))
extern unsigned char D_0034E100[];
extern unsigned char D_0034E140[];
unsigned int func_002B0B78(D *d, int n);
void _sceMpegError(D *d, const char *msg);
int _sceMpegDispatchMpegCallback(void *mp, CB *cb);
void func_002B2EB8(D *d);
int func_002980D0(void);
int func_00298120(void);
void func_002B2CE8(D *d);
void func_002B20E8(void *mp);
static inline void _loadQM(D *d, unsigned char *qm, unsigned int cmd)
{
    CB cb;
    int e;

    cb.type = 2;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    func_002B2EB8(d);
    R(0x10002000) = 0;
    func_002B2EB8(d);
    e = func_002980D0();
    R(0x1000B410) = (unsigned int)qm & 0x0FFFFFFF;
    R(0x1000B420) = 4;
    R(0x1000B400) = 0x101;
    if (e)
        func_00298120();
    R(0x10002000) = cmd;
    d->cmd = cmd & 0xF0000000;
    d->x828 = 1;
    func_002B2EB8(d);
    cb.type = 3;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
}
void func_002B2400(D *d)
{
    unsigned int v;
    int vs;

    d->xE8 = 0;
    v = func_002B0B78(d, 32);
    vs = (v >> 8) & 0xFFF;
    d->hsize = v >> 20;
    d->vsize = vs;
    if (vs > 2800)
        _sceMpegError(d, "vertical size > 2800");
    v = func_002B0B78(d, 30);
    d->bit_rate = v >> 12;
    d->vbv_size = (v >> 1) & 0x3FF;
    if ((d->load_intra = func_002B0B78(d, 1))) {
        func_002B2EB8(d);
        R(0x10002000) = 0x50000000;
        d->cmd = 0x50000000;
        d->x828 = 1;
        func_002B2EB8(d);
    } else {
        _loadQM(d, D_0034E100, 0x50000000);
    }
    if ((d->load_nonintra = func_002B0B78(d, 1))) {
        func_002B2EB8(d);
        R(0x10002000) = 0x58000000;
        d->cmd = 0x50000000;
        d->x828 = 1;
        func_002B2EB8(d);
    } else {
        _loadQM(d, D_0034E140, 0x58000000);
    }
    func_002B2CE8(d);
    func_002B20E8(d->mp);
}

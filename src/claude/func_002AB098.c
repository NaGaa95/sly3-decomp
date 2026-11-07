// Sly 2 counterpart: _sceMpegCscStoreRefImage (decomp src/lib/_sceMpegCscStoreRefImage.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* func_002AB098 (libmpeg, Claude agent): DMA the reference image to the IPU (toIPU ch4, chunked via the
   func_002AB6B8 handler when > 0xFFFF qw) and CSC it back (fromIPU ch3; func_002AAED8 for >= 0x400 MBs). The CSC part is an
   inline function used twice; the IPU command helper sets d->x82C/x828. */
typedef struct { int type; int pad[7]; } CB;
typedef struct { unsigned int size; unsigned int addr; int pad[2]; } ST;
typedef struct { unsigned int addr; int x4; int x8; int w; int h; } P;
typedef struct {
    char p0[0xEC]; unsigned int xEC;
    char pF0[0x828 - 0xF0]; int x828; int x82C;
    char p830[0x868 - 0x830]; void *mp;
} D;
#define R(a) (*(volatile unsigned int *)(a))
#define RS(a) (*(volatile int *)(a))
int func_002AB6B8(int ch, void *arg);
int func_002933C0(int ch, int (*h)(int, void *), int next, void *arg);
int func_002933D0(int ch, int id);
int func_00293EC8(int ch);
int func_00293E60(int ch);
void func_00293920(int);
int func_002980D0(void);
int func_00298120(void);
int _sceMpegDispatchMpegCallback(void *mp, CB *cb);
void func_002AAED8(D *d, unsigned int out, int n);

static inline void ipuCmd(D *d, unsigned int cmd)
{
    R(0x10002000) = cmd;
    d->x82C = cmd & 0xF0000000;
    if ((cmd & 0xF0000000) == 0x20000000 || (cmd & 0xF0000000) == 0x30000000 || (cmd & 0xF0000000) == 0x40000000)
        d->x828 = 0;
    else
        d->x828 = 1;
}

static inline void cscStore(D *d, int n)
{
    CB cb2;
    CB *pcb;
    unsigned int out;
    int qwc;
    int e;
    if (n < 0x400) {
        out = d->xEC;
        pcb = &cb2;
        qwc = n << 6;
        while (RS(0x10002010) < 0)
            ;
        e = func_002980D0();
        { volatile unsigned int *m = (void *)0x1000B010, *q = (void *)0x1000B020, *c = (void *)0x1000B000;
        *m = out & 0x0FFFFFFF;
        *q = qwc;
        *c = 0x100; }
        if (e)
            func_00298120();
        ipuCmd(d, n | 0x70000000);
        pcb->type = 4;
        _sceMpegDispatchMpegCallback(d->mp, &cb2);
        while ((R(0x1000B000) >> 8) & 1)
            ;
        while (RS(0x10002010) < 0)
            ;
    } else {
        func_002AAED8(d, d->xEC, n);
    }
}

void func_002AB098(D *d, P *p)
{
    CB cb;
    ST st;
    int n, id, e;

    n = p->w * p->h;
    cb.type = 2;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    if (R(0x10002010) & 0x4000)
        R(0x10002010) = 0x40000000;
    while (RS(0x10002010) < 0)
        ;
    ipuCmd(d, 0);
    while (RS(0x10002010) < 0)
        ;
    func_00293920(0);
    st.addr = p->addr & 0x0FFFFFFF;
    st.size = n * 0x18;
    if (st.size > 0xFFFF) {
        id = func_002933C0(4, func_002AB6B8, 0, &st);
        R(0x1000E010) = 0x10;
        func_00293EC8(4);
        e = func_002980D0();
        { volatile unsigned int *m = (void *)0x1000B410, *q = (void *)0x1000B420, *c = (void *)0x1000B400;
        *m = st.addr;
        *q = 0xFFFF;
        *c = 0x101; }
        if (e)
            func_00298120();
        st.addr = (st.addr + 0xFFFF0) & 0x0FFFFFFF;
        st.size -= 0xFFFF;
        cscStore(d, n);
        func_00293E60(4);
        func_002933D0(4, id);
    } else {
        e = func_002980D0();
        { volatile unsigned int *m = (void *)0x1000B410, *q = (void *)0x1000B420, *c = (void *)0x1000B400;
        *m = p->addr & 0x0FFFFFFF;
        *q = st.size;
        *c = 0x101; }
        if (e)
            func_00298120();
        st.size = 0;
        cscStore(d, n);
    }
    cb.type = 3;
    _sceMpegDispatchMpegCallback(d->mp, &cb);
}

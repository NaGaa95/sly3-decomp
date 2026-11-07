// Sly 2 counterpart: sceCdRead (decomp src/lib/sceCdRead.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char trycount, spindlctrl, datapattern, pad; } sceCdRMode;
typedef struct {
    unsigned int lbn;
    unsigned int sectors;
    void *buf;
    sceCdRMode mode;
    void *eedest;
    void *eeaddr;
} CdReadArg;
extern volatile int D_0034C3B8;
extern int D_0034C390;
extern volatile int _sceCd_mode;
extern volatile int D_0034C3B4;
extern volatile int D_0034C3A8;
extern CdReadArg D_0034C480;
extern char D_0034D480[];
extern int _sceCd_readpos;
extern char D_0034D550[];
extern char D_0032B758[];
extern char D_0032B770[];
void func_0029FF70(void *);
int func_002A03E8(void);
int func_002A0290(int);
void func_00299DF0(void *, int);
int func_002955E0(const char *, ...);
int func_002936C0(int);
int func_00295F08(void *, int, unsigned int, void *, int, void *, int, void *, void *);
int func_002A0E38(unsigned int lbn, unsigned int sectors, void *buf, sceCdRMode *mode)
{
    CdReadArg *rd = &D_0034C480;
    int size;
    if (!(D_0034C3B8 & 1)) {
        if (func_002A03E8() == 6)
            return 0;
    }
    if (func_002A0290(4) == 0)
        return 0;
    rd->lbn = lbn;
    rd->sectors = sectors;
    rd->buf = buf;
    rd->mode.trycount = mode->trycount;
    rd->mode.spindlctrl = mode->spindlctrl;
    rd->mode.datapattern = mode->datapattern;
    rd->eedest = D_0034D480;
    rd->eeaddr = &_sceCd_readpos;
    switch (mode->datapattern) {
    case 1:
        size = sectors * 2328;
        break;
    case 2:
        size = sectors * 2340;
        break;
    case 0:
    default:
        size = sectors << 11;
        break;
    }
    _sceCd_readpos = 0;
    if (!(D_0034C3B8 & 2))
        func_00299DF0(buf, size);
    func_00299DF0(D_0034D480, 0x90);
    func_00299DF0(rd, 0x18);
    func_00299DF0(&_sceCd_readpos, 4);
    if (D_0034C390 > 0)
        func_002955E0(D_0032B758);
    _sceCd_mode = 1;
    D_0034C3B4 = 1;
    if (func_00295F08(D_0034D550, 1, 1, rd, 0x18, 0, 0, func_0029FF70, D_0034D480) < 0) {
        _sceCd_mode = 0;
        D_0034C3B4 = 0;
        func_002936C0(D_0034C3A8);
        return 0;
    }
    if (D_0034C390 > 0)
        func_002955E0(D_0032B770);
    return 1;
}

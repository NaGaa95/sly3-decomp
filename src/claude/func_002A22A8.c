// Sly 2 counterpart: sceMcInit (decomp src/lib/sceMcInit.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
extern RpcCD D_004D1200;
extern char D_004D1280[];
extern int D_004D27C0[];
extern int D_0034DF94;
extern int D_0034DF98;
extern char D_0032B900[], D_0032B910[], D_0032B928[], D_0032B940[], D_0032B968[];
int func_002936A0(struct SemaParam *);
int func_002936B0(int);
int func_002936C0(int);
int func_002936E0(int);
void func_002A2A48(int, int, int);
void func_002956E0(int);
int func_002955E0(const char *, ...);
int func_00295D28(void *, unsigned int, int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
static inline int bindmc(void)
{
    if (func_00295D28(&D_004D1200, 0x80000400, 0) < 0) {
        func_002955E0(D_0032B928);
        while (1) ;
    }
    return D_004D1200.server;
}
int func_002A22A8(void)
{
    struct SemaParam sp;
    int i = 0;
    int j;
    int r;

    if (D_0034DF94 < 0) {
        int m1 = -1;
        sp.initCount = 1;
        sp.option = (unsigned int)D_0032B900;
        sp.maxCount = 1;
        D_0034DF94 = func_002936A0(&sp);
        if (D_0034DF94 == m1)
            return -101;
        sp.maxCount = 1;
        sp.initCount = 0;
        sp.option = (unsigned int)D_0032B910;
        r = func_002936A0(&sp);
        D_0034DF98 = r;
        if (r == m1) {
            func_002936B0(D_0034DF94);
            D_0034DF94 = r;
            return -101;
        }
    }
    func_002A2A48(0, 0, 0);
    func_002936E0(D_0034DF94);
    func_002956E0(0);
    while (bindmc() == 0) {
        j = 0x100000;
        while (--j) ;
        if (++i >= 0x200) {
            func_002955E0(D_0032B928);
            return -91;
        }
    }
    r = func_00295F08(&D_004D1200, 0xFE, 0, D_004D1280, 0x30, D_004D27C0, 0xC, 0, 0);
    func_002936C0(D_0034DF94);
    if (r < 0) {
        D_004D1200.server = 0;
        return -91;
    }
    if (D_004D27C0[1] < 0x20A) {
        func_002955E0(D_0032B940);
        D_004D1200.server = 0;
        return -120;
    }
    if (D_004D27C0[2] < 0x20E) {
        func_002955E0(D_0032B968);
        D_004D1200.server = 0;
        return -121;
    }
    return D_004D27C0[0];
}

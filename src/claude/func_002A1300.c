// Sly 2 counterpart: scePadInit (decomp src/lib/scePadInit.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; char q[0x28 - 0x28]; } RpcCD;
extern RpcCD D_004D0F00[2];
extern int D_0034DF48;
extern int D_0034DF4C;
extern char D_0032B7D0[];
extern char D_0032B7F8[];
int func_00295D28(void *, unsigned int, int);
int func_002A2238(void);
int func_002955E0(const char *, ...);
int func_002A1488(int);
int func_002A1300(int mode)
{
    int i;
    int ver;
    D_0034DF48 = 1;
    while (func_00295D28(&D_004D0F00[0], 0x80000100, 0), D_004D0F00[0].server == 0) {
        i = 0x10000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    while (func_00295D28(&D_004D0F00[1], 0x80000101, 0), D_004D0F00[1].server == 0) {
        i = 0x10000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    ver = func_002A2238();
    if ((ver >> 8) != 4) {
        if (D_0034DF4C) {
            func_002955E0(D_0032B7D0);
            func_002955E0(D_0032B7F8, 4, 0, ver >> 8, ver & 0xFF);
        }
        return 0;
    }
    return func_002A1488(mode);
}

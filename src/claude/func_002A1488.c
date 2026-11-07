// Sly 2 counterpart: scePadInit2 (decomp src/lib/scePadInit2.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int a, b, c, d, e, f, g; } PadSlot;
extern PadSlot D_004D0F50[2][4];
extern char D_004D0F00[];
extern int D_004D1140[];
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002980D0(void);
int func_00298120(void);
void func_00299A28(int, void *, void *);
int func_002A1440(void *);
int func_002A1488(int mode)
{
    int i;
    int s;
    for (i = 0; i < 4; i++) {
        D_004D0F50[0][i].e = 0;
        D_004D0F50[0][i].g = 0;
        D_004D0F50[0][i].f = 0;
        D_004D0F50[1][i].e = 0;
        D_004D0F50[1][i].g = 0;
        D_004D0F50[1][i].f = 0;
    }
    D_004D1140[0] = 0x10;
    D_004D1140[4] = 0;
    if (func_00295F08(D_004D0F00, 1, 0, D_004D1140, 0x80, D_004D1140, 0x80, 0, 0) < 0)
        return 0;
    s = func_002980D0();
    func_00299A28(0x80000019, func_002A1440, 0);
    if (s == 1) func_00298120();
    return D_004D1140[3];
}

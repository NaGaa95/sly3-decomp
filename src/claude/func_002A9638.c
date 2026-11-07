// Sly 2 counterpart: _clearEach (decomp src/lib/_clearEach.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
#define R(a) (*(volatile unsigned int *)(a))
typedef struct { char p0[0x1C0]; int x1C0; char p1[0x828 - 0x1C4]; int x828; } MpegD;
int func_002980D0(void);
int func_00298120(void);
void func_002B35F0(int, int);
void func_002A9638(MpegD *d)
{
    int r;
    d->x828 = 1;
    d->x1C0 = 0;
    r = func_002980D0();
    R(0x1000F590) = R(0x1000F520) | 0x10000;
    R(0x1000B000) = 0;
    R(0x1000B400) = 0;
    R(0x1000D400) = 0;
    R(0x1000F590) = R(0x1000F520) & ~0x10000;
    if (r) func_00298120();
    R(0x1000B020) = 0;
    R(0x1000B420) = 0;
    R(0x1000D420) = 0;
    R(0x10002010) = 0x40000000;
    func_002B35F0(0, 0);
}

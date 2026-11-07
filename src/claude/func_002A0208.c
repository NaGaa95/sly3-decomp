// Sly 2 counterpart: PowerOffCB (decomp src/lib/PowerOffCB.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern int D_0034C3A4;
extern volatile int D_0034C3C8;
int func_002980D0(void);
int func_00299A28(int, void *, int);
int func_00298120(void);
void func_002A01B0(void);
int func_002A0208(void)
{
    int e;
    D_0034C3A4 = 1;
    e = func_002980D0();
    func_00299A28(0x80000012, func_002A01B0, 0);
    if (e) func_00298120();
    D_0034C3A4 = 0;
    D_0034C3C8 = 1;
    return 1;
}

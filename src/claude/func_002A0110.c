// Sly 2 counterpart: cdvd_exit (decomp src/lib/cdvd_exit.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// volatile store/load keep Sony's source order (store of -1 before the sema-id load)
extern int D_0034C394;
extern volatile int _sceCd_mode;
extern int D_0034C3A0;
extern int D_0034C3A8;
extern int D_0034C3AC;
extern int D_0034C3B0;
int func_002936C0(int);
int func_002936B0(int);
int func_002980D0(void);
int func_00298120(void);
int sceSifRemoveCmdHandler(unsigned int);
void func_002A0110(void)
{
    int r;
    if (D_0034C394) {
        _sceCd_mode = -1;
        func_002936C0(*(volatile int *)&D_0034C3A0);
    }
    func_002936B0(D_0034C3A8);
    func_002936B0(D_0034C3AC);
    func_002936B0(D_0034C3B0);
    func_002936B0(D_0034C3A0);
    r = func_002980D0();
    sceSifRemoveCmdHandler(0x80000012);
    if (r) func_00298120();
}

// Sly 2 counterpart: func_002418D0 (decomp src/lib/func_002418D0.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern volatile int _sceCd_mode;
extern volatile int D_0034C3E4;
extern volatile int D_0034C3B4;
extern volatile int D_0034C3A8;
extern volatile int D_0034C394;
extern volatile int D_0034C3A0;
extern volatile int D_004D0C40;
int func_002936D0(int);
void func_0029FEC8(int *data)
{
    _sceCd_mode = *data;
    D_0034C3E4 = _sceCd_mode;
    if (_sceCd_mode == 11) {
        _sceCd_mode = 0;
        D_0034C3B4 = 0;
        return;
    }
    func_002936D0(D_0034C3A8);
    if (D_0034C394 != 0 && D_004D0C40 != 0)
        func_002936D0(D_0034C3A0);
    else
        D_0034C3B4 = 0;
    _sceCd_mode = 0;
}

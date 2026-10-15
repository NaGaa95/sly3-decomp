// Free consumes actual allocation A0, moves it to explicit11E1F0 A1, and supplies original fixed pool00479CB0 A0. No other incoming input is consumed.
// SLY3_CFLAGS: -Os -G0
extern char D_00479CB0[];
void func_0011E1F0(void *pool,void *allocation);
void func_0020BBB0(void *allocation){func_0011E1F0(D_00479CB0,allocation);}

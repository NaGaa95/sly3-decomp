// Free consumes actual allocation A0, moves it to explicit11E1F0 A1, and supplies original fixed pool00479CC8 A0. No other incoming input is consumed.
// SLY3_CFLAGS: -Os -G0
extern char D_00479CC8[];
void func_0011E1F0(void *pool,void *allocation);
void func_0020BBF8(void *allocation){func_0011E1F0(D_00479CC8,allocation);}

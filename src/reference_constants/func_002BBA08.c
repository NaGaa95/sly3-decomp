// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original pool startup reset. Independent scalar writes precede the first clear.
extern int D_0036AE14, D_0036AE18, D_0036AE1C, D_0036AE20, D_0036AE24;
extern unsigned char D_004D2AF0[];
extern unsigned char D_004D2B30[];
extern unsigned char D_004D2BB0[];
extern void *memset(void *destination, int value, unsigned int bytes);
extern void func_0011E210(void *pool);

void func_002BBA08(void)
{
    D_0036AE24 = 0;
    D_0036AE14 = 0;
    D_0036AE20 = 0;
    D_0036AE1C = 0;
    memset(D_004D2B30, 0, 128);
    D_0036AE18 = 0;
    memset(D_004D2AF0, 0, 64);
    func_0011E210(D_004D2BB0);
}

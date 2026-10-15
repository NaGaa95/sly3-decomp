// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original pool startup reset. Independent scalar writes precede the first clear.
extern int D_0036AE00, D_0036AE04, D_0036AE08, D_0036AE0C, D_0036AE10;
extern unsigned char D_004D2A18[];
extern unsigned char D_004D2A58[];
extern unsigned char D_004D2AD8[];
extern void *memset(void *destination, int value, unsigned int bytes);
extern void func_0011E210(void *pool);

void func_002BB928(void)
{
    D_0036AE10 = 0;
    D_0036AE00 = 0;
    D_0036AE0C = 0;
    D_0036AE08 = 0;
    memset(D_004D2A58, 0, 128);
    D_0036AE04 = 0;
    memset(D_004D2A18, 0, 64);
    func_0011E210(D_004D2AD8);
}

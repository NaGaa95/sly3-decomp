// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64

extern unsigned char D_0034A604[4];
extern unsigned char *D_0034A6B0;
extern unsigned char D_004CC728[4];
int func_00291DF8(const void *left, const void *right, unsigned int bytes);

int func_00296A60(void)
{
    unsigned char *expected = D_0034A604;
    unsigned char *current = D_004CC728;
    int different = 0;

    if (func_00291DF8(current, expected, 4) != 0) {
        if (func_00291DF8(current, D_0034A6B0, 4) != 0) {
            different = func_00291DF8(expected, D_0034A6B0, 4) != 0;
        }
    }
    return different;
}

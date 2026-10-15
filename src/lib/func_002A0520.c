// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64
// SLY3_AS: gnu-2.9

extern int D_0034C390;
extern char D_0032B670[];
extern unsigned char D_0034DF00[];
int func_002955E0(const char *format, ...);
int func_00294198(int microseconds);
int func_00296108(void *rpc);

int func_002A0520(int mode)
{
    if (mode == 0) {
        if (D_0034C390 > 0)
            func_002955E0(D_0032B670);
        while (func_00296108(D_0034DF00))
            func_00294198(4000);
        return 0;
    }
    return func_00296108(D_0034DF00);
}

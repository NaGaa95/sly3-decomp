// Sly 2 counterpart: log10 (decomp src/lib/log10.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
struct exception {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
    int err;
};
extern const int D_0032C2F0;
extern double D_0032C2E8;
double func_002A48E8(double x);
int func_002A86A8(double x);
int matherr(struct exception *x);
int *func_0029EE48(void);
double func_002A3770(double x)
{
    double z;
    struct exception exc;
    z = func_002A48E8(x);
    if (D_0032C2F0 == -1 || func_002A86A8(x)) return z;
    if (x <= 0.0) {
        exc.name = "log10";
        exc.err = 0;
        exc.arg1 = x;
        exc.arg2 = x;
        if (D_0032C2F0 == 0)
            exc.retval = -3.40282346638528859812e+38;
        else
            exc.retval = -D_0032C2E8;
        if (x == 0.0) {
            exc.type = 2;
            if (D_0032C2F0 == 2)
                *func_0029EE48() = 34;
            else if (!matherr(&exc)) {
                *func_0029EE48() = 33;
            }
        } else {
            exc.type = 1;
            if (D_0032C2F0 == 2)
                *func_0029EE48() = 33;
            else if (!matherr(&exc)) {
                *func_0029EE48() = 33;
            }
        }
        if (exc.err != 0)
            *func_0029EE48() = exc.err;
        return exc.retval;
    } else
        return z;
}

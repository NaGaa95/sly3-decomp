// Sly 2 counterpart: fmodf (decomp src/lib/fmodf.c)
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
float func_002A6810(float x, float y);
int func_002A8AE8(float x);
int matherr(struct exception *x);
int *func_0029EE48(void);
float func_002A4188(float x, float y)
{
    struct exception exc;
    float z;

    z = func_002A6810(x, y);
    if (D_0032C2F0 == -1 || func_002A8AE8(y) || func_002A8AE8(x))
        return z;
    if (y == (float)0.0) {
        exc.type = 1;
        exc.name = "fmodf";
        exc.err = 0;
        exc.arg1 = (double)x;
        exc.arg2 = (double)y;
        if (D_0032C2F0 == 0)
            exc.retval = x;
        else
            exc.retval = 0.0 / 0.0;
        if (D_0032C2F0 == 2)
            *func_0029EE48() = 33;
        else if (!matherr(&exc)) {
            *func_0029EE48() = 33;
        }
        if (exc.err != 0)
            *func_0029EE48() = exc.err;
        return (float)exc.retval;
    } else
        return z;
}

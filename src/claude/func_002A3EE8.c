// Sly 2 counterpart: atan2f (decomp src/lib/atan2f.c)
// (Claude agent) only diff: Sony gas nop between c.eq/c.lt.s and bc1f (libm FPU compare hazard, toolchain); otherwise exact.
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
float __ieee754_atan2f(float y, float x);
int func_002A8AE8(float x);
int matherr(struct exception *x);
int *func_0029EE48(void);
float func_002A3EE8(float y, float x)
{
    struct exception exc;
    float z;

    z = __ieee754_atan2f(y, x);
    if (D_0032C2F0 == -1 || func_002A8AE8(x) || func_002A8AE8(y))
        return z;
    if (x == (float)0.0 && y == (float)0.0) {
        exc.arg1 = (double)y;
        exc.arg2 = (double)x;
        exc.type = 1;
        exc.name = "atan2f";
        exc.err = 0;
        exc.retval = 0.0;
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

// Sly 2 counterpart: acosf (decomp src/lib/acosf.c)
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
float func_002A5AA0(float x);
int func_002A8AE8(float x);
float func_002A34F0(float x);
int matherr(struct exception *x);
int *func_0029EE48(void);
float func_002A3CE8(float x)
{
    struct exception exc;
    float z;

    z = func_002A5AA0(x);
    if (D_0032C2F0 == -1 || func_002A8AE8(x))
        return z;
    if (func_002A34F0(x) > (float)1.0) {
        exc.type = 1;
        exc.name = "acosf";
        exc.err = 0;
        exc.arg1 = exc.arg2 = (double)x;
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

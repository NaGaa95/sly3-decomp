// func_002A4010: expf (newlib wf_exp.c wrapper around __ieee754_expf = func_002A6558)
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
extern const double D_0032C2E8;
float func_002A6558(float x);
int func_002A8AC0(float x);
int matherr(struct exception *x);
int *func_0029EE48(void);
static const float
o_threshold=  8.8721679688e+01,
u_threshold= -1.0397208405e+02;
float func_002A4010(float x)
{
    float z;
    struct exception exc;
    z = func_002A6558(x);
    if (D_0032C2F0 == -1) return z;
    if (func_002A8AC0(x)) {
        if (x > o_threshold) {
            exc.type = 3;
            exc.name = "expf";
            exc.err = 0;
            exc.arg1 = exc.arg2 = (double)x;
            if (D_0032C2F0 == 0)
                exc.retval = ((float)3.40282346638528859812e+38);
            else
                exc.retval = D_0032C2E8;
            if (D_0032C2F0 == 2)
                *func_0029EE48() = 34;
            else if (!matherr(&exc)) {
                *func_0029EE48() = 34;
            }
            if (exc.err != 0)
                *func_0029EE48() = exc.err;
            return (float)exc.retval;
        } else if (x < u_threshold) {
            exc.type = 4;
            exc.name = "expf";
            exc.err = 0;
            exc.arg1 = exc.arg2 = (double)x;
            exc.retval = 0.0;
            if (D_0032C2F0 == 2)
                *func_0029EE48() = 34;
            else if (!matherr(&exc)) {
                *func_0029EE48() = 34;
            }
            if (exc.err != 0)
                *func_0029EE48() = exc.err;
            return (float)exc.retval;
        }
    }
    return z;
}

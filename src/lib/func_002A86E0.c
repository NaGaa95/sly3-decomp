// Reference: Sly 2 src/lib/matherr.c; target Sly 3 0x002A86E0.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int dpcmp(double, double);
struct exception { int type; char *name; double arg1; };
int matherr(struct exception *x)
{
    int n = 0;
    if (x->arg1 != x->arg1) return 0;
    return n;
}

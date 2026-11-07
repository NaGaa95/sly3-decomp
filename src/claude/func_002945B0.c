// Sly 2 counterpart: printfloat (decomp src/lib/printfloat.c)
// WIP (Claude agent): 4/118 diffs. Only the order of `lui s3,%hi("0.%d")` (PRE edge insertion in both branches) vs `daddu a0,s0` in the two branch delay slots after the d<0.1 / d>=1.0 tests. Needs -msoft-float; `else if (d >= 1.0) while (...)` gives the target's guarded jump-to-test loop; func_00294520 result in a local fixes the format-address s-reg.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -msoft-float
// SLY3_ASM: gnu-reorder-db
typedef int (*PutFunc)(void *, int *, int);
int func_00294520(unsigned long);
int func_00295548(PutFunc, void *, int *, const char *, ...);
int func_002945B0(PutFunc put, void *arg, int *w, double d)
{
    int n = 0;
    int e = 0;
    if (*w == 0) return 0;
    if (d < 0) {
        d = 0 - d;
        n = 1;
        put(arg, w, '-');
        (*w)--;
    }
    if (d < 0.1) {
        while (d < 0.1) {
            d *= 10.0;
            e--;
        }
    } else if (d >= 1.0) {
        while (d >= 1.0) {
            d /= 10.0;
            e++;
        }
    }
    {
        int v = func_00294520((unsigned long)(d * 1000000.0));
        n += func_00295548(put, arg, w, "0.%d", v);
    }
    if (e >= 0)
        n += func_00295548(put, arg, w, "e+%d", e);
    else
        n += func_00295548(put, arg, w, "e%d", e);
    return n;
}

// Sly 2 counterpart: _sceSnprintf_pf (decomp src/lib/_sceSnprintf_pf.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
int func_00294788(void *a, void *b, int n, const char *fmt, va_list ap);
int func_00295548(void *a, void *b, int *pn, const char *fmt, ...)
{
    va_list ap;
    int r;

    va_start(ap, fmt);
    r = func_00294788(a, b, *pn, fmt, ap);
    *pn -= r;
    return r;
}

// Sly 2 counterpart: sceSnprintf (decomp src/lib/sceSnprintf.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
#define va_end(ap)
int func_002954A0(char **pp, int *left, int c);
int func_00294788(int (*put)(char **, int *, int), char **ctx, unsigned int size, const char *fmt, va_list ap);
int func_00295598(char *buf, unsigned int size, const char *fmt, ...)
{
    va_list ap;
    char *p = buf;
    int r;
    va_start(ap, fmt);
    r = func_00294788(func_002954A0, &p, size, fmt, ap);
    va_end(ap);
    return r;
}

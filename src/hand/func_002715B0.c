// Reconstructed using the corresponding Sly 2 source and checked against Sly 3.
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
int func_00271570(void *f, char *fmt, va_list ap);
int func_002715B0(void *f, char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    return func_00271570(f, fmt, ap);
}

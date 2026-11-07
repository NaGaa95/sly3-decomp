// Sly 2 counterpart: func_00236960 (decomp src/lib/func_00236960.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef char *va_list;
int func_002980D0(void);
int func_00298120(void);
int func_002954F8(void *, int);
int func_00294788(int (*)(void *, int), void *, unsigned int, const char *, va_list);
void func_002955E0(const char *fmt, ...)
{
    int buf[4];
    va_list ap;
    int st;
    buf[0] = 0;
    st = func_002980D0();
    ap = (char *)__builtin_next_arg(fmt) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    func_00294788(func_002954F8, buf, 0xFFFFFFFF, fmt, ap);
    if (st) func_00298120();
}

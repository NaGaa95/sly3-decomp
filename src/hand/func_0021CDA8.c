// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
/* EE (single-float EABI) stdarg, from gcc's va-mips.h */
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
struct MSG { int cb; int nKind; };
void *func_001D25B0(struct MSG *pmsg);
void func_0021CBC0(void *p, va_list ap, void *pv);
void *func_0021CDA8(void *p, ...) {
    struct MSG msg;
    va_list ap;
    void *pv;
    va_start(ap, p);
    msg.cb = 8;
    msg.nKind = 0x10;
    pv = func_001D25B0(&msg);
    func_0021CBC0(p, ap, pv);
    return pv;
}

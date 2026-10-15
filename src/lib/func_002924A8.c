// Sly 2 reference: src/lib/func_00233828.c.
// Actual Sly 3 reentrancy pointer and noreturn process exit call are relocated below.
// SLY3_CFLAGS: -O2 -G0
struct _atexit { struct _atexit *_next; int _ind; void (*_fns[32])(void); };
struct _reent { char pad[0x3C]; void (*__cleanup)(struct _reent *); char pad2[0x148 - 0x40]; struct _atexit *_atexit; };
extern struct _reent *D_0034A5F4;
void func_00100218(int) __attribute__((noreturn));

void func_002924A8(int code)
{
    struct _atexit *p;
    int n;
    for (p = D_0034A5F4->_atexit; p; p = p->_next)
        for (n = p->_ind; --n >= 0;)
            (*p->_fns[n])();
    if (D_0034A5F4->__cleanup)
        (*D_0034A5F4->__cleanup)(D_0034A5F4);
    func_00100218(code);
}

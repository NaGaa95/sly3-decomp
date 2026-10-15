// Sly 2 reference: src/hand/func_001D88D0.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
struct MSG { int cb; int nKind; };
struct FRAME {
    int a[4];
    FRAME();
    ~FRAME();
};
struct V { int c; void *pv; };
V *func_001D2470(MSG *pmsg) __asm__("func_001D2470");
void *func_001D24D0(MSG *pmsg, void *pv) __asm__("func_001D24D0");
void func_0021CBC0(void *p, va_list ap, V *pv) __asm__("func_0021CBC0");
extern "C" V *func_0021CCD0(void *p, ...) __asm__("func_0021CCD0");
extern "C" V *func_0021CCD0(void *p, ...)
{
    FRAME frame;
    MSG msg;
    MSG *pmsg = &msg;
    va_list ap;
    V *pv;
    va_start(ap, p);
    pmsg->cb = 8;
    pmsg->nKind = 0x10;
    pv = func_001D2470(pmsg);
    func_0021CBC0(p, ap, pv);
    {
        void *pvOld = pv->pv;
        pmsg->cb = pv->c * 2;
        pmsg->nKind = 0x10;
        pv->pv = func_001D24D0(pmsg, pvOld);
    }
    return pv;
}

// Sly 2 reference: src/hand/func_0013E5E0.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
class X;
typedef void (X::*PMF)(void *);
struct D { int id; PMF pmf; };
extern "C" char D_00475480[];
extern "C" void *func_0017E1B8(void *, int, int, X *) __asm__("func_0017E1B8");
extern "C" void func_001508B0(X *p, D *pd) __asm__("func_001508B0");
extern "C" void func_001508B0(X *p, D *pd)
{
    void *pv = func_0017E1B8(D_00475480, 4, pd->id, p);
    (p->*(pd->pmf))(pv);
}

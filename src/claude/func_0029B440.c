// Sly 2 counterpart: __muldi3 (decomp src/lib/__muldi3.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef int SItype __attribute__((mode(SI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
struct DIstruct { SItype low, high; };
typedef union { struct DIstruct s; DItype ll; } DIunion;
#define umul_ppmm(w1, w0, u, v) \
  __asm__ ("multu %2,%3" : "=l" ((USItype) w0), "=h" ((USItype) w1) : "d" ((USItype) u), "d" ((USItype) v))
#define __umulsidi3(u, v) ({ DIunion __w; umul_ppmm (__w.s.high, __w.s.low, u, v); __w.ll; })
DItype func_0029B440(DItype u, DItype v)
{
    DIunion w;
    DIunion uu, vv;
    uu.ll = u, vv.ll = v;
    umul_ppmm(w.s.high, w.s.low, uu.s.low, vv.s.low);
    w.s.high += ((USItype) uu.s.low * (USItype) vv.s.high
                 + (USItype) uu.s.high * (USItype) vv.s.low);
    return w.ll;
}

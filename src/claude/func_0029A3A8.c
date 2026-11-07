// Sly 2 counterpart: func_0023B728 (decomp src/lib/func_0023B728.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* libgcc2.c (L__main) __do_global_ctors, without the atexit call; D_0034E200 = __CTOR_LIST__.
   The do { } while (0) of gbl-ctors.h's DO_GLOBAL_CTORS_BODY macro is what gives the target's register
   allocation (loop counter in $s1, strength-reduced pointer in $s0). */
typedef void (*func_ptr)(void);
extern func_ptr D_0034E200[];
#define __CTOR_LIST__ D_0034E200

#define DO_GLOBAL_CTORS_BODY						\
do {									\
  unsigned long nptrs = (unsigned long) __CTOR_LIST__[0];		\
  unsigned i;								\
  if (nptrs == (unsigned long)-1)				        \
    for (nptrs = 0; __CTOR_LIST__[nptrs + 1] != 0; nptrs++);		\
  for (i = nptrs; i >= 1; i--)						\
    __CTOR_LIST__[i] ();						\
} while (0)

void func_0029A3A8(void)
{
    DO_GLOBAL_CTORS_BODY;
}

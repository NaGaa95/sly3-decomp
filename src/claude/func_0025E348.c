// SLY3_CFLAGS: -Os -G0
// Count the entries of a group and how many of them have "is_complete" set (Splice lookups through func_002BC010).
// (A64) Find() inline keeps &D as a base pseudo ((hi+lo)+8 per call); zero-insn asm on f raises its alloc priority so &ref is rematerialized.
#include "eval_dispatch_api.h"
struct E { int c; void **ap; };
struct KEY { int n; short *ps; };
struct SYMTAB { int f0; int pad; char sym[1]; };
extern struct SYMTAB D_004793C8;
void *memset(void *, int, int);
short func_0021CB20(void *psym, const void *pv);
CRef *func_002BC010(CRef *output, struct KEY *key, void *pv);
static inline short Find(struct SYMTAB *pst, const void *pv) { return func_0021CB20(pst->sym, pv); }
void func_0025E348(struct E *pe, int *pc0, int *pc1, void *pv)
{
    int c0 = 0;
    int c1 = 0;
    if (D_004793C8.f0 && pe && pe->c) {
        short as[8];
        struct KEY k, k0;
        int i = 0;
        memset(&k0, 0, 8);
        k0.n = 2;
        k0.ps = as;
        k = k0;
        k.ps[1] = Find(&D_004793C8, "is_complete");
        while (i < pe->c) {
            CRef ref;
            int f;
            k.ps[0] = Find(&D_004793C8, pe->ap[i++]);
            c0++;
            func_002BC010(&ref, &k, pv);
            f = ref.payload.integer;
            __asm__("" : : "r"(f));
            func_0012BC20(&ref);
            if (f)
                c1++;
        }
    }
    if (pc0)
        *pc0 = c0;
    if (pc1)
        *pc1 = c1;
}

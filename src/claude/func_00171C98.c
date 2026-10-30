// SLY3_CFLAGS: -Os -G0
#include "../../include/eval_dispatch_api.h"
struct KEY;
struct S0 { char pad[8]; struct KEY *pkey; float g; int f; };
struct S1 { char pad[0x50]; int n; };
struct S2 { char pad[0xAC]; float *pg; };
extern struct S1 *D_004BC244;
extern struct S2 *D_004794C4;
extern unsigned char D_00468D30[];
int func_0025E150(void);
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
static inline float GGet(struct S0 *p)
{
    if (p->f) {
        CRef value;
        unsigned int bits;
        func_002BC010(&value, p->pkey, D_00468D30);
        bits = value.payload.integer;
        func_0012BC20(&value);
        p->g = 0.0f;
        for (; bits; bits >>= 1)
            if (bits & 1) p->g += 0.03125f;
        p->f = 0;
    }
    return p->g;
}
float func_00171C98(struct S0 *p)
{
    int n;
    if (func_0025E150() == 0x16) return 1.0f;
    n = -1;
    if (D_004BC244) n = D_004BC244->n;
    if (n == 0 || n == 2) return 0.0f;
    return D_004794C4 ? *D_004794C4->pg : p->pkey ? GGet(p) : 0.0f;
}

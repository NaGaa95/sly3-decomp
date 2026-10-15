// Reference algorithm: src/hand/func_0012EC50.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
#include "actor_state_resource_api.h"
typedef struct AREQ { int cb; int cbAlign; } AREQ;
typedef struct REC { int id; float v[2]; float g; } REC;
typedef struct T { char pad[0xD0]; int c; void *pad2; void **ap; int crec; REC *arec; } T;
typedef struct G { char pad[0x238]; void *p; } G;
extern G D_00474FF0;
void func_001C7DC8(T *t);
void **func_001D2538(AREQ *preq);
void func_00131128(T *t)
{
    AREQ req;
    void *p;
    func_001C7DC8(t);
    req.cb = t->c * 4;
    req.cbAlign = 0x10;
    t->ap = func_001D2538(&req);
    p = D_00474FF0.p;
    if (p) {
        int i;
        for (i = 0; i < t->crec; i++) {
            REC *prec = &t->arec[i];
            func_002462B8(p, func_002489A0(&D_00474FF0, prec->id), t, prec->g, prec->v);
        }
    }
}

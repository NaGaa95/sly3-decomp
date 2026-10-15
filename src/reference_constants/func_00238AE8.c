#include "owned_record_list_api.h"
// Reference algorithm: src/hand/func_001EF0D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE {
    short d;
    short pad;
    void (*pf)(void *);
};
struct OW {
    char pad[0x29C];
    struct ActorOwnedRecordList list;
};
struct O {
    char pad[0xC];
    struct VTE *vt;
    struct OW *pow;
};
struct S {
    struct O *po;
};
void func_00238AE8(void *receiver) {
    struct S *p = (struct S *)receiver;
    struct O *po = p->po;
    if (po) {
        void *px = &po->pow->list;
        po->vt[9].pf((char *)po + po->vt[9].d);
        func_00238770(px);
        p->po = 0;
    }
}

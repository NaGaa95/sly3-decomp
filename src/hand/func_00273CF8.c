#include "heap_frame_api.h"
// Deserialize the state collection, allocate and resize its 144-byte records, and resolve the optional owner link using the Sly 3 descriptor ID and flag bit.
// Reference algorithm: src/hand/func_00220FD0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct MARK {
    int a[4];
}
MARK;
typedef struct MSG {
    int cb;
    int nKind;
    int k;
    int **pp;
}
MSG;
struct O {
    char pad[0x28];
    long bits;
};
struct S {
    char pad[0xE0];
    char aE4[0x18];
    char aFC[0x10];
    struct O *p10C;
    int c;
    void *a;
    void *cur;
    int x11C;
    char pad2[0x12C - 0x11C];
    int flags;
};
void func_00290438(struct S *p, void *pbis);
void func_001193F8(void *pbis, void *pv);
void func_00119640(void *pbis, void *pv, void *pv2);
void *func_001D25B0(MSG *pmsg);
void *func_001D24D0(MSG *pmsg, void *pv);
void func_00274530(struct S *p, int id);
void func_001519C8(struct S *p, void *pbis);
void func_00274660(struct S *p);
void func_00151A38(MSG *pmsg);
void func_002904B0(struct S *p, void *pbis, MSG *pmsg);
void func_00273CF8(struct S *p, void *pbis) {
    MARK mark;
    MSG msg;
    void *pv;
    func_00290438(p, pbis);
    func_001193F8(pbis, p->aE4);
    func_00119640(pbis, p->aE4, p->aFC);
    func_001D2770(&mark);
    {
        MSG *pm = &msg;
        pm->cb = 0x240;
        pm->nKind = 0x10;
        p->a = func_001D25B0(pm);
    }
    func_00274530(p, 0x2F);
    func_001519C8(p, pbis);
    func_00274660(p);
    {
        MSG *pm = &msg;
        pm->cb = p->c * 0x90;
        pm->nKind = 0x10;
        pv = func_001D24D0(pm, p->a);
    }
    p->x11C = 1;
    p->a = pv;
    p->cur = pv;
    func_00151A38(&msg);
    func_002904B0(p, pbis, &msg);
    switch (msg.k) {
        case 0: break;
        case 1: p->p10C = (struct O *)*msg.pp;
        p->p10C->bits |= 1L << 53;
        break;
    }
    if (!p->p10C) p->flags &= ~2;
    func_001D2798(&mark, 2);
}

// Reference algorithm: src/hand/func_0015C320.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct MSG { int cb; int nKind; } MSG;
void *func_001D24D0(MSG *pmsg, void *pv);
static inline void *PvReallocMsg(MSG *pmsg, void *pv, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D24D0(pmsg, pv); }
struct S { int pad[4]; void *p10; char pad2[0xD0 - 0x14]; int c; void **apv; };
void func_0028FE20(struct S *p, void *pv);
void *func_001507E0(void *pv, void *p10);
void func_00179FE0(struct S *p, void *pv)
{
    MSG msg;
    int i;
    func_0028FE20(p, pv);
    p->apv = PvReallocMsg(&msg, p->apv, p->c * 4, 0x10);
    for (i = 0; i < p->c; i++)
        p->apv[i] = func_001507E0(p->apv[i], p->p10);
}

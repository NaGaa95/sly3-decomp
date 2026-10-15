// Reference algorithm: src/hand/func_001DE518.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct S { char pad[0x178]; int c; void *pv; };
void func_0023F400(struct S *p, void *source);
void *func_001D24D0(struct MSG *pmsg, void *pv);
static inline void *PvReallocMsg(struct MSG *pmsg, int cb, int nKind, void *pv) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D24D0(pmsg, pv); }
void func_002239B8(struct S *p, void *source) {
    struct MSG msg;
    func_0023F400(p, source);
    p->pv = PvReallocMsg(&msg, p->c * 0x170, 0x10, p->pv);
}

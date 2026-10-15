// Initialize the inherited object, clear the used count, and allocate all requested 16-byte records.
// Reference algorithm: src/hand/func_001BC088.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct S { char pad[0x130]; int c; int used; void *p; };
void func_0023C580(struct S *p);
void *func_001D2538(struct MSG *pmsg);
static __inline__ void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D2538(pmsg); }
void func_00279778(struct S *p)
{
    struct MSG msg;
    func_0023C580(p);
    p->used = 0;
    p->p = PvAllocMsg(&msg, p->c << 4, 0x10);
}

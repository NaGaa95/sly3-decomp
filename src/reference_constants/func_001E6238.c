// Reference algorithm: src/hand/func_001BC088.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct S { char pad[0xD8]; int c; char pad2[0x1EC - 0xEC]; void *p; };
void func_0022D780(struct S *p);
void *func_001D2538(struct MSG *pmsg);
static __inline__ void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001D2538(pmsg); }
void func_001E6238(struct S *p)
{
    struct MSG msg;
    func_0022D780(p);
    p->p = PvAllocMsg(&msg, (p->c << 4) - 0x10, 0x10);
}

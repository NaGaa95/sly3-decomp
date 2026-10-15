// Reference algorithm: src/hand/func_001E9C30.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

struct MSG { int cb; int nKind; };
struct S { char pad[0x170]; void *pv; };
void *func_001D2538(struct MSG *pmsg);
void func_002319A0(void *pv, struct S *p);
void func_00231948(struct S *p)
{
    struct MSG msg;
    if (!p->pv) {
        msg.cb = 0x9C;
        msg.nKind = 0x10;
        p->pv = func_001D2538(&msg);
        func_002319A0(p->pv, p);
    }
}

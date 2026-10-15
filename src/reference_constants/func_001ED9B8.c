// Reference algorithm: src/hand/func_001C10C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct G { char pad[0x4DF8]; void *p45c8; void *p45cc; };
void *func_00150690(int a, int b, int c, int d);
void func_001ECEC0(void *p);
void *func_001D2538(struct MSG *pmsg);
void func_001EDA28(void *p);
void func_001ED9B8(struct G *p)
{
    if (!p->p45cc) {
        struct MSG msg;
        p->p45c8 = func_00150690(0x10, 0, 0x321, -1);
        func_001ECEC0(p->p45c8);
        msg.cb = 0x30;
        msg.nKind = 0x10;
        p->p45cc = func_001D2538(&msg);
    }
    func_001EDA28(p->p45cc);
}

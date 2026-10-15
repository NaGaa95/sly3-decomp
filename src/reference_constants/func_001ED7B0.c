// Reference algorithm: src/hand/func_001C0EC0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct G { char pad[0x4DFC]; void *p45cc; };
int func_001190A8(void *pbis);
void *func_001D2538(struct MSG *pmsg);
void func_001ED820(void *p, int n, void *pbis);
void func_001ED7B0(struct G *p, void *pbis)
{
    int n = func_001190A8(pbis);
    if (n) {
        struct MSG msg;
        msg.cb = 0x30;
        msg.nKind = 0x10;
        p->p45cc = func_001D2538(&msg);
        func_001ED820(p->p45cc, n, pbis);
    }
}

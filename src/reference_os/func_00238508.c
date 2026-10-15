// Sly 2 reference: src/hand/func_001EEC70.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct MSG { int cb; int nKind; };
struct S { int a, b; void *ap[8]; };
int func_001158A0(void);
void *func_001D2470(struct MSG *pmsg);
void func_00238508(struct S *p)
{
    unsigned int i;
    struct MSG msg;
    for (i = 0; i < 8; i++) {
        msg.cb = func_001158A0();
        msg.nKind = 0x10;
        p->ap[i] = func_001D2470(&msg);
    }
}

// Reference algorithm: src/hand/func_001DDF00.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x60]; int n; };
struct E { struct O *po; int a, b; };
struct G2 { char pad[0x58]; int c; struct E ae[1]; };
extern struct G2 D_0046FAA0;
extern struct G D_00475480;
const unsigned short *func_00150630(struct G *g, int n);
unsigned short *func_00271730(unsigned short *p, const unsigned short *q);
void func_00222630(unsigned short *p, int i) {
    struct G2 *pg = &D_0046FAA0;
    if (i < pg->c) func_00271730(p, func_00150630(&D_00475480, pg->ae[i].po->n));
}

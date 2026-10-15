// Reference algorithm: src/hand/func_0022D6B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x44]; int base; };
extern int D_004C4130;
extern int D_004C4138[];
int func_0028C250(int a, struct S *b, struct S *c)
{
    int r = 0;
    switch (a & 0x3000) {
    case 0: if (c) r = c->base + (a << 8); break;
    case 0x1000: a &= ~0xF000; r = b->base + (a << 8); break;
    case 0x2000: r = D_004C4138[D_004C4130 - 1]; break;
    }
    return r;
}

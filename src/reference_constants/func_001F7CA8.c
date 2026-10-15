// Reference algorithm: src/hand/func_001C67D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char p0[0x154]; float x1A0; char p1[0x174 - 0x158]; float x1D0, x1D4, x1D8, x1E0, x1E4; int unknown188; float x1DC;
    char p2[0x1A0 - 0x190]; float x230, x234; int x238; int x23C; int x240; };
void func_001F65F0(struct S *p);
void func_001F7CA8(struct S *p)
{
    func_001F65F0(p);
    p->x1D8 = 45.0f;
    p->x1DC = 75.0f;
    p->x1D0 = 250.0f;
    p->x1D4 = 50.0f;
    p->x1E4 = 0.2f;
    p->x1E0 = 0.65f;
    p->x1A0 = 0.25f;
    p->x23C = 10;
    p->x240 = 20;
    p->x230 = 4.0f;
    p->x234 = 5.0f;
}

// Reference algorithm: src/hand/func_001C6508.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x154]; float a1A0; char p1[0x174 - 0x158]; float a1D0, a1D4, a1D8, a1E0, a1E4; int unknown188; float a1DC; char p2[0x1A0 - 0x190]; float a230, a234; };
void func_001F65F0(struct S *p);
void func_001F79A0(struct S *p)
{
    func_001F65F0(p);
    p->a1D8 = 45.0f;
    p->a1DC = 65.0f;
    p->a1D0 = 250.0f;
    p->a1D4 = 150.0f;
    p->a1E0 = 0.5f;
    p->a1E4 = 0.25f;
    p->a1A0 = 0.25f;
    p->a230 = 5.0f;
    p->a234 = 5.0f;
}
